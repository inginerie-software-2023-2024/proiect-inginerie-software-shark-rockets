import pytest
from consts import UserExecutable as UE
import data
from utils import assert_log_chain

@pytest.mark.parametrize("job_type", [UE.SAMPLE, UE.WORD_COUNTER, UE.REAL_ESTATE])
def test_run_jobs(user_code, job_type):
    job = user_code(job_type)
    job.wait_for_process_exit()
    assert_log_chain([
        job.later_wait_on_log_contains("Binary running in user mode"),
        job.later_wait_on_log_contains("succes")
    ])
