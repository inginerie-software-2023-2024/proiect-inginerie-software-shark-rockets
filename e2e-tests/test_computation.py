import pytest
from consts import UserExecutable as UE
import data
from utils import assert_log_chain

def test_run_sample(user_code):
    sample_job = user_code(UE.SAMPLE)
    sample_job.wait_for_process_exit()
    assert_log_chain([
        sample_job.later_wait_on_log_contains("Binary running in user mode"),
        sample_job.later_wait_on_log_contains("succes")
    ])
    
def test_run_wc(user_code):
    wc_job = user_code(UE.WORD_COUNTER)
    wc_job.wait_for_process_exit()
    assert_log_chain([
        wc_job.later_wait_on_log_contains("Binary running in user mode"),
        wc_job.later_wait_on_log_contains("succes")
    ])