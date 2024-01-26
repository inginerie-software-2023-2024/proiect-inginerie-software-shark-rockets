import pytest
from consts import UserExecutable as UE
import data

def test_run_sample(master,user_code):
    sample_job = user_code(UE.SAMPLE)
    sample_job.wait_for_process_exit()
    master.dump_logs_timed()
    assert sample_job.wait_on_log_contains("success") != None
    
def test_run_wc(user_code):
    wc_job = user_code(UE.WORD_COUNTER)
    wc_job.wait_for_process_exit()
    assert wc_job.wait_on_log_contains("success") != None