import subprocess
import threading
import queue
import pytest
import os
import time
import uuid
import re
import consts
import utils
import data
class SubprocessRunner:
    def __init__(self, command: consts.Executable, args: list):
        unique_id = str(uuid.uuid4())
        timestamp = time.strftime("%Y%m%d%H%M%S")
        log_filename = f"custom_log_file_{timestamp}_{unique_id}.log"
        binary_path = os.path.join(consts.PATH_NFS, command.value)
        full_command = [binary_path] + args + ['--log-file', log_filename]
        self.log_file_path = os.path.join('./logs', log_filename)

        self.process = subprocess.Popen(
            full_command, 
            stdout=subprocess.DEVNULL, 
            stderr=subprocess.DEVNULL
        )
        self.log_queue = queue.Queue()

        def wait_for_log_file_creation(log_file_path):
            while not os.path.exists(log_file_path):
                time.sleep(0.1)
        wait_for_log_file_creation(self.log_file_path)

        self._start_threads()

    def _start_threads(self):
        def monitor_log_file(log_file_path, queue):
            with open(log_file_path, 'r') as file:
                while True:
                    line = file.readline()
                    if not line:
                        if self.process.poll() is not None:
                            break
                        time.sleep(0.1)
                        continue
                    queue.put(line)

        thread = threading.Thread(target=monitor_log_file, args=(self.log_file_path, self.log_queue))
        thread.daemon = True
        thread.start()

    def _wait_for_condition(self, check_condition, timeout):
        start_time = time.time()
        while True:
            try:
                if timeout != None:
                    elapsed_time = time.time() - start_time
                    if elapsed_time >= timeout:
                        return None
                    wait_time = timeout - elapsed_time
                else:
                    wait_time = None

                line = self.log_queue.get(timeout=wait_time)
                if check_condition(line):
                    return line
            except queue.Empty:
                continue

    def wait_on_log(self, timeout=consts.SANITY_TIMEOUT):
        return self._wait_for_condition(lambda _: True, timeout)

    def wait_on_log_contains(self, substring, timeout=consts.SANITY_TIMEOUT):
        return self._wait_for_condition(lambda line: substring in line, timeout)

    def wait_on_log_match_regex(self, pattern, timeout=consts.SANITY_TIMEOUT):
        compiled_pattern = re.compile(pattern)
        return self._wait_for_condition(lambda line: compiled_pattern.search(line), timeout)
    
    def dump_logs_timed(self,wait=None):
        start_time = time.time()
        while True:
            log = self.wait_on_log(timeout=0.1)
            if log != None:
                print(log)
            elif wait == None:
                return
            
            elapsed_time = time.time() - start_time
            if wait != None and elapsed_time > wait:
                return

    def wait_for_process_exit(self, timeout=consts.SANITY_TIMEOUT):
        start_time = time.time()
        while True:
            exit_code = self.process.poll()
            if exit_code is not None:
                return exit_code
            
            elapsed_time = time.time() - start_time
            if elapsed_time > timeout:
                return None

            time.sleep(0.1) 

    def terminate(self):
        if self.process.poll() is None:
            self.process.terminate()
        self.process.wait()

    def clean(self):
        if os.path.exists(self.log_file_path):
            os.remove(self.log_file_path)

class Master(SubprocessRunner):
    def __init__(self, args=[]):
        super().__init__(consts.Executable.MASTER, args)

class Worker(SubprocessRunner):
    def __init__(self, args=[]):
        super().__init__(consts.Executable.WORKER, args)
        self.register_log = (self.wait_on_log_contains("Worker: listening on port") != None)
    def wait_serving(self):
        self.wait_on_log_contains("SERVING")
    def registered(self):
        return self.register_log
        
class User():
    def __init__(self,email="guest"):
        self.email = email
    def dir(self):
        return self.email

class UserCode(SubprocessRunner):
    def __init__(self,user:User,user_executable:consts.UserExecutable,args=[]):
        data.gen_data(user,user_executable)
        super().__init__(user_executable,args + ["--mode","user"])
    

# XXX temporary, params once eucalypt once eucalypt auth
@pytest.fixture(scope="session")
def guest():
    guest = User()
    yield guest

@pytest.fixture
def master():
    master_instance = Master()
    yield master_instance
    master_instance.terminate()
    master_instance.clean()

# factory worker fixture
@pytest.fixture
def worker(master):
    worker_instances = []
    
    def _make_worker(port:int,args:list=[]) -> Worker:
        worker_instance = Worker(["--port",f"{port}"] + args)
        worker_instances.append(worker_instance)
        return worker_instance
    
    yield _make_worker
    
    for worker_instance in worker_instances:
        worker_instance.terminate()
        worker_instance.clean()
        
@pytest.fixture(params=[1,2,5])
def worker_cluster(worker,request):
    workers = []
    for i in range(request.param):
        workers.append(worker(consts.START_PORT + i))
    for worker in workers:
        worker.wait_serving()
    yield workers
    
@pytest.fixture
def user_code(guest,worker_cluster):
    instances = []
    
    def _make_job(job:consts.UserExecutable,args:list=[]) -> UserCode:
        instance = UserCode(guest,job)
        instances.append(instance)
        return instance
    
    yield _make_job
    
    for instance in instances:
        instance.terminate()
        instance.clean()

@pytest.fixture(scope="session", autouse=True)
def nfs_file_sync():
    utils.sync(consts.PATH_TO_PACKAGE, consts.PATH_NFS)
    yield
