import pytest
from consts import UserExecutable as UE
import itertools
from utils import assert_log_chain
import solvers

job_types = [UE.SAMPLE, UE.WORD_COUNTER, UE.REAL_ESTATE]
all_combinations = []
for r in range(1, len(job_types) + 1):
    all_combinations.extend(itertools.combinations(job_types, r))

@pytest.mark.parametrize("job_type", job_types)
def test_run_jobs(user_job, job_type):
    job = user_job(job_type)
    job.wait_for_process_exit()
    assert_log_chain([
        job.later_wait_on_log_contains("Binary running in user mode"),
        job.later_wait_on_log_contains("succes")
    ])

@pytest.mark.parametrize("job_combination", all_combinations)
def test_run_multiple_jobs(user_job, job_combination):
    jobs = []
    for job_type in job_combination:
        job = user_job(job_type)
        jobs.append(job)

    for job in jobs:
        job.wait_for_process_exit()
        assert_log_chain([
            job.later_wait_on_log_contains("Binary running in user mode"),
            job.later_wait_on_log_contains("succes")
        ])
        
def test_sample_correctness(user_job):
    job = user_job(UE.SAMPLE)
    job.wait_for_process_exit()
    out = job.output()
    data = job.input()
    correct = solvers.sample(data)
    assert out == correct
    
def test_wc_correctness(user_job):
    job = user_job(UE.WORD_COUNTER)
    job.wait_for_process_exit()
    out = job.output()
    data = job.input()
    correct = solvers.word_counter(data)
    assert out == correct


def test_real_estate_correctness(user_job):
    job = user_job(UE.REAL_ESTATE)
    job.wait_for_process_exit()
    out = job.output()
    data = job.input()
    correct = solvers.real_estate(data)
    assert out == correct

@pytest.mark.parametrize("job_type", job_types)
def test_run_jobs_unstable(unstable_user_job, job_type):
    job = unstable_user_job(job_type)
    job.wait_for_process_exit()
    assert_log_chain([
        job.later_wait_on_log_contains("Binary running in user mode"),
        job.later_wait_on_log_contains("succes")
    ])

@pytest.mark.parametrize("job_combination", all_combinations)
def test_run_multiple_jobs_unstable(unstable_user_job, job_combination):
    jobs = []
    for job_type in job_combination:
        job = unstable_user_job(job_type)
        jobs.append(job)

    for job in jobs:
        job.wait_for_process_exit()
        assert_log_chain([
            job.later_wait_on_log_contains("Binary running in user mode"),
            job.later_wait_on_log_contains("succes")
        ])

def test_sample_correctness_unstable(unstable_user_job):
    job = unstable_user_job(UE.SAMPLE)
    job.wait_for_process_exit()
    out = job.output()
    data = job.input()
    correct = solvers.sample(data)
    assert out == correct


def test_wc_correctness_unstable(master,unstable_user_job):
    job = unstable_user_job(UE.WORD_COUNTER)
    job.wait_for_process_exit()
    out = job.output()
    data = job.input()
    correct = solvers.word_counter(data)
    assert out == correct

def test_real_estate_correctness_unstable(unstable_user_job):
    job = unstable_user_job(UE.REAL_ESTATE)
    job.wait_for_process_exit()
    out = job.output()
    data = job.input()
    correct = solvers.real_estate(data)
    assert out == correct
