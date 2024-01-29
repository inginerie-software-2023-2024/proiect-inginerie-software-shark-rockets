# This suite is for the basic functionalities of the app ass well as the testing infrastructure
# as the name suggest it checks if when turning on koala smoke comes out
import pytest
import consts

def test_master_listening(master):
    log = master.wait_on_log_contains("Master: listening")
    assert log != None

@pytest.mark.parametrize("worker_count", [1, 2, 5, 10, 100])
def test_multiple_workers(worker, worker_count):
    workers = []

    for i in range(worker_count):
        workers.append(worker(consts.START_PORT + i))

    for worker_instance in workers:
        assert worker_instance.registered()
    
def test_cluster(master,worker_cluster):
    for worker in worker_cluster:
        assert worker.registered()

    pattern = r"Master: received a register worker request: ip: \d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}, port: \d+"
    for _ in worker_cluster:
        log = master.wait_on_log_match_regex(pattern)
        assert log != None
