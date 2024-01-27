import pytest 
from utils import assert_log_chain

def test_master_notices_dead_worker(master,worker):
    worker1 = worker(7777)
    worker1.wait_serving()
    worker1.terminate()
    assert_log_chain(
        [master.later_wait_on_log_contains("Health check stream failed: Socket closed")] +
        [master.later_wait_on_log_contains("Health check stream failed:",timeout=100) for _ in range(6)] +
        [master.later_wait_on_log_contains("Marking worker as inactive")]
    )
