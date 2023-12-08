#include "master_state.hpp"
#include <stdexcept>

MasterState::MasterState()
    : pending_tasks_semaphore(std::counting_semaphore(0)),
      run_assign_tasks_thread(true) {
  // start the thread that assigns pending tasks to workers
  assign_tasks_thread = std::thread(&MasterState::assign_tasks, this);
}

void MasterState::push_worker(std::unique_ptr<Worker> new_worker) {
  std::lock_guard<std::mutex> lock(master_lock);
  workers.push_back(std::move(new_worker));
}

std::unique_ptr<Worker> MasterState::pop_worker() {
  std::lock_guard<std::mutex> lock(master_lock);

  if (workers.empty())
    throw std::runtime_error("No registered workers!");

  // Find the worker with the lowest load.
  auto best = workers.begin();
  for (auto iter = workers.begin() + 1; iter != workers.end(); iter++) {
    if ((*iter)->load() < (*best)->load()) {
      best = iter;
    }
  }

  std::unique_ptr to_return = std::move(*best);
  workers.erase(best);
  return to_return;
}

void MasterState::setup_job(const std::string& job_uuid,
                            const std::string& job_user,
                            const std::string& binary_path,
                            const std::string& mapper_name,
                            const std::string& reducer_name) {
  std::lock_guard<std::mutex> lock(master_lock);

  // store job metadata
  job_metadata.insert({job_uuid, Job(job_uuid, job_user, binary_path,
                                     mapper_name, reducer_name)});
}

void MasterState::start_map_leg(const std::string& job_uuid,
                                const std::vector<nfs::fs::path>& job_files) {
  std::lock_guard<std::mutex> lock(master_lock);

  // set the current leg of the job as the map leg
  current_job_leg.insert({job_uuid, JobLeg::MapLeg});
  expected_tasks[job_uuid] = {};

  // init tasks belonging to this job_leg
  for (std::size_t i = 0; i < job_files.size(); i++) {
    Task task(job_uuid, {job_files[i]});
    std::string task_uuid = task.get_task_uuid();
    task_metadata.insert({task_uuid, task});
    expected_tasks[job_uuid].insert(task_uuid);
    pending_tasks.push_back(task_uuid);
  }

  // wake up the assign_tasks thread
  pending_tasks_semaphore.release();
}

void MasterState::assign_tasks() {
  while (run_assign_tasks_thread) {
    // wait for pending tasks
    pending_tasks_semaphore.acquire();

    // retrieve pending tasks
    std::vector<std::string> tasks_to_assign;
    master_lock.lock();
    std::swap(tasks_to_assign, pending_tasks);
    master_lock.unlock();

    std::cout << "There are " << tasks_to_assign.size() << " tasks to assign\n";
    for (const auto& task_uuid : tasks_to_assign) {
      auto task = task_metadata.at(task_uuid);
      auto job = job_metadata.at(task.get_job_uuid());
      auto job_leg = current_job_leg[job.get_job_uuid()];

      auto worker = pop_worker();

      std::cout << "Assign task " << task_uuid << " to " << worker->address()
                << ":" << worker->port() << " with load = " << worker->load()
                << ", input file: " << task.get_job_input_files()[0].string()
                << std::endl;

      worker->assign_work(job.get_binary_path(),
                          (job_leg == JobLeg::MapLeg) ? WorkerType::Mapper
                                                      : WorkerType::Reducer,
                          job.get_exec_class(job_leg),
                          task.get_job_input_files()[0].string());

      push_worker(std::move(worker));
    }
  }
}

MasterState::~MasterState() {
  // terminate the thread that assigns pending tasks to workers
  run_assign_tasks_thread = false;
  pending_tasks_semaphore.release();
  assign_tasks_thread.join();
}
