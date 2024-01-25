# This suite is for the basic functionalities of the app ass well as the testing infrastructure
# as the name suggest it checks if when turning on koala smoke comes out
import pytest
import time


@pytest.mark.parametrize('master_args', [[], ["--thread-id"]])
def test_master_listening(master):
    log = master.wait_on_log()
    print(log)
    assert log != None

@pytest.mark.parametrize('worker_args', [[]])
def test_worker(worker):
    log = worker.wait_on_log()
    print(log)
    assert log != None
