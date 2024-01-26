import pytest
from consts import UserExecutable as UE
import data

def test_run_sample(user_code):
    sample_job = user_code(UE.SAMPLE)
    sample_job.wait_for_process_exit()
    
import time
def test_run_wc(master,user_code):
    time.sleep(1) # comment this for failure, check logs
    wc_job = user_code(UE.WORD_COUNTER)
    wc_job.wait_for_process_exit()
    master.dump_logs_timed()
    wc_job.dump_logs_timed()
