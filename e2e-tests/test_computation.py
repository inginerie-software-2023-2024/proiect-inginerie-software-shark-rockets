import pytest
from consts import UserExecutable as UE
import itertools
from utils import assert_log_chain

job_types = [UE.SAMPLE, UE.WORD_COUNTER, UE.REAL_ESTATE]
all_combinations = []
for r in range(1, len(job_types) + 1):
    all_combinations.extend(itertools.combinations(job_types, r))

@pytest.mark.parametrize("job_type", job_types)
def test_run_jobs(user_code, job_type):
    job = user_code(job_type)
    job.wait_for_process_exit()
    assert_log_chain([
        job.later_wait_on_log_contains("Binary running in user mode"),
        job.later_wait_on_log_contains("succes")
    ])

@pytest.mark.parametrize("job_combination", all_combinations)
def test_run_multiple_jobs(user_code, job_combination):
    jobs = []
    for job_type in job_combination:
        job = user_code(job_type)
        jobs.append(job)

    for job in jobs:
        job.wait_for_process_exit()
        assert_log_chain([
            job.later_wait_on_log_contains("Binary running in user mode"),
            job.later_wait_on_log_contains("succes")
        ])
