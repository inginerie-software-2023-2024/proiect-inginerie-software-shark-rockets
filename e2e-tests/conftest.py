import subprocess
import threading
import queue
import pytest
import os
import time
import uuid
import re
import consts
class SubprocessRunner:
    def __init__(self, command: consts.Executable, args: list):
        unique_id = str(uuid.uuid4())
        timestamp = time.strftime("%Y%m%d%H%M%S")
        log_filename = f"custom_log_file_{timestamp}_{unique_id}.log"
        binary_path = os.path.join(consts.PATH_TO_PACKAGE, command.value)
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
                if timeout != float('inf'):
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
    
    def _make_worker(port:int) -> Worker:
        worker_instance = Worker(["--port",f"{port}"])
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
    yield workers

