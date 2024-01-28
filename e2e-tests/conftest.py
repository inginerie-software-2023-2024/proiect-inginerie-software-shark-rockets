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
import shutil
import random
from functools import lru_cache
import eucalypt_endpoint as api

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
        self.log_storage = []

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
                    self.log_storage.append(line)

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
    
    def later_wait_on_log(self, timeout=consts.SANITY_TIMEOUT):
        return lambda: self._wait_for_condition(lambda _: True, timeout)

    def later_wait_on_log_contains(self, substring, timeout=consts.SANITY_TIMEOUT):
        return lambda: self._wait_for_condition(lambda line: substring in line, timeout)

    def later_wait_on_log_match_regex(self, pattern, timeout=consts.SANITY_TIMEOUT):
        compiled_pattern = re.compile(pattern)
        return lambda: self._wait_for_condition(lambda line: compiled_pattern.search(line), timeout)
        
    def dump_logs_timed(self, wait=None):
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
    def _dump_logs_storage(self, wait=None):
        start_time = time.time()
        while True:
            log = self.wait_on_log(timeout=0.1)
            if log != None:
                self.log_storage.append(log)
            elif wait == None:
                return
            
            elapsed_time = time.time() - start_time
            if wait != None and elapsed_time > wait:
                return

    def wait_for_process_exit(self, timeout=None):
        start_time = time.time()
        while True:
            exit_code = self.process.poll()
            if exit_code is not None:
                return exit_code
            
            elapsed_time = time.time() - start_time
            if timeout!=None and elapsed_time > timeout:
                return -1

            time.sleep(0.1)

    def terminate(self):
        if self.process.poll() is None:
            self.process.terminate()
        self.process.wait()

    def clean(self):
        log_dir = "./logs"
        if os.path.exists(log_dir):
            shutil.rmtree(log_dir)

    def _assert_no_error(self):
        self._dump_logs_storage()
        for log in self.log_storage:
            if "ERROR" in log:
                raise Exception(f"Error found in logs: {log}")
            
    def teardown(self):
        self.terminate()
        self._assert_no_error()
        self.clean()
        
    def find_log(self, pattern, timeout=consts.SANITY_TIMEOUT):
        compiled_pattern = re.compile(pattern)

        # First, check the existing logs
        for log in self.log_storage:
            if compiled_pattern.search(log):
                return log

        # If not found, wait for new logs
        return self.wait_on_log_match_regex(pattern, timeout)

class Master(SubprocessRunner):
    def __init__(self, args=[]):
        super().__init__(consts.Executable.MASTER, args)
    def wait_on_validation(self):
        self.wait_on_log_contains("Validating token")
        self.wait_on_log_contains("Token answer received")

class Worker(SubprocessRunner):
    def __init__(self, args=[]):
        super().__init__(consts.Executable.WORKER, args)
        self.register_log = (self.wait_on_log_contains("Worker: listening on port") != None)
    def wait_serving(self):
        self.wait_on_log_contains("SERVING")
    def registered(self):
        return self.register_log
        
class User():
    def __init__(self,email="user",password=None):
        self.email = email
        if password:
            self.password = password
            self.uuid = api.get_id(self.email,self.password)
    
    def uses_token(self):
        return hasattr(self,'uuid')
    
    def get_token(self):
        if not self.uses_token():
            return None
        return api.generate_token(self.uuid)
    def dir(self):
        return self.email

class UserCode(SubprocessRunner):
    def __init__(self,user:User,user_executable:consts.UserExecutable,args=[]):
        self.user=user
        data.gen_data(user,user_executable)
        extra_args = ["--mode","user"]
        token = user.get_token()
        if token:
            extra_args += ["--token",token]
        super().__init__(user_executable,args+extra_args)
        
    @lru_cache(maxsize=1)
    def get_uuid(self): # best effort, will rotate logs in memory, but the user code has only 5 logs so it shouldn't be a problem
        pattern = r"Job uuid is \[.*\]"
        uuid_log = self.find_log(pattern)
        if uuid_log:
            start_phrase = "Job uuid is ["
            start_index = uuid_log.find(start_phrase)
            if start_index != -1:
                start_index += len(start_phrase)
                end_index = uuid_log.find(']', start_index)
                if end_index != -1:
                    return uuid_log[start_index:end_index]
        raise ValueError("cannot aquire job uuid")
    
    def job_dir(self):
        return f"{consts.PATH_NFS}/{self.user.dir()}/job-{self.get_uuid()}"
    
    def output(self):
        out_dir = f"{self.job_dir()}/output"
        iterators = utils.get_file_iterators(out_dir)
        serialize = utils.serialize_iterators(iterators)
        if len(serialize[0].split()) == 1:
            result = {x for x in serialize}
        else:
            result = {k: v for k, v in (item.split() for item in serialize)}
        return result
    
    def input(self):
        out_dir = f"{self.job_dir()}/input"
        iterators = utils.get_file_iterators(out_dir)
        return utils.serialize_iterators(iterators)
        
    def clean_nfs(self):
        shutil.rmtree(self.job_dir())
    

@pytest.fixture(scope="session",params=consts.USERS)
def user(eucalypt,request):
    creds = consts.USERS_CREDS[request.param]
    user = User(creds['email'],creds['password'])
    yield user

@pytest.fixture
def master():
    master_instance = Master()
    yield master_instance
    master_instance.teardown()

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
        worker_instance.teardown()
        
@pytest.fixture(params=consts.CLUSTER_SIZES)
def worker_cluster(worker,request):
    workers = [worker(consts.START_PORT + i) for i in range(request.param)]
    for worker in workers:
        worker.wait_serving()
    yield workers
    for worker in workers:
        worker.teardown()
    
def terminate_workers_randomly(workers, percentage):    
    num_workers = len(workers)
    num_to_terminate = max(1, int(num_workers * percentage / 100))

    # Ensure at least one worker remains
    if num_to_terminate >= num_workers:
        num_to_terminate = num_workers - 1

    workers_to_terminate = random.sample(workers, num_to_terminate)
    for worker in workers_to_terminate:
        worker.terminate()

@pytest.fixture(params=[(size, percent) for size in consts.CLUSTER_SIZES for percent in consts.FAULTY_PERCENT])
def unstable_worker_cluster(worker, request):
    cluster_size, terminate_percentage = request.param
    workers = [worker(consts.START_PORT + i) for i in range(cluster_size)]
    for worker in workers:
        worker.wait_serving()

    terminator_thread = threading.Thread(target=terminate_workers_randomly, args=(workers, terminate_percentage))
    terminator_thread.start()

    yield workers

    terminator_thread.join()

    for worker in workers:
        worker.teardown()
    
@pytest.fixture
def user_job(user,master,worker_cluster):
    instances = []
    
    def _make_job(job:consts.UserExecutable,args:list=[]) -> UserCode:
        if instances and user.uses_token():
            master.wait_on_validation()
        instance = UserCode(user,job)
        instances.append(instance)
        return instance
    
    yield _make_job
    
    for instance in instances:
        instance.teardown()
        instance.clean_nfs()

@pytest.fixture
def unstable_user_job(user,unstable_worker_cluster):
    instances = []
    
    def _make_job(job:consts.UserExecutable,args:list=[]) -> UserCode:
        time.sleep(1) # wait a second so that the unstable workers are killed, master will have to reassign to finish the job
        instance = UserCode(user,job)
        instances.append(instance)
        return instance
    
    yield _make_job
    
    for instance in instances:
        instance.teardown()
        instance.clean_nfs()

@pytest.fixture(scope="session", autouse=True)
def nfs_file_sync():
    utils.sync(consts.PATH_TO_PACKAGE, consts.PATH_NFS)
    yield

@pytest.fixture(scope="session")
def eucalypt():
    original_directory = os.getcwd()
    os.chdir(consts.PATH_EUCALYPT_BACKEND)
    
    instance = subprocess.Popen(
            ['npm','run','start:dev'], 
            stdout=subprocess.DEVNULL, 
            stderr=subprocess.DEVNULL
        )
    os.chdir(original_directory)
    time.sleep(5) # wait for backend
    yield
    os.chdir(consts.PATH_EUCALYPT_BACKEND)
    instance.terminate()
    instance.wait()
    subprocess.run(["pkill","node"]) # XXX npm seems to start 3 node process, instance.terminate() only kills one, but pkill is a bit
    subprocess.run(["npm","run","clear"]) # clear db
    os.chdir(original_directory)
