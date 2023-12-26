#include "master_state.hpp"
#include <stdexcept>
#include "logging.hpp"

MasterState::MasterState()
    : pending_tasks_semaphore(std::counting_semaphore(0)),
      run_assign_tasks_thread(true) {
  // start the thread that assigns pending tasks to workers
  assign_tasks_thread = std::thread(&MasterState::assign_tasks, this);
}

void MasterState::create_worker(const std::string& addr, const int listen_port,
                                const int emit_port) {
  auto dump_work_on_failure =
      [&master_lock = master_lock, &pending_tasks = pending_tasks,
       &pending_tasks_semaphore = pending_tasks_semaphore](
          const std::unordered_set<std::string>& tasks) {
        std::lock_guard<std::mutex> lock(master_lock);

        for (const auto& task_uuid : tasks) {
          pending_tasks.push_back(task_uuid);
        }
        pending_tasks_semaphore.release();
      };
  auto worker = std::make_unique<Worker>(addr, listen_port, emit_port,
                                         dump_work_on_failure);
  push_worker(std::move(worker));
}

void MasterState::push_worker(std::unique_ptr<Worker> new_worker) {
  std::lock_guard<std::mutex> lock(worker_dict_lock);
  if (!new_worker->is_active()) {
    // worker is unresponsive, lazily delete it on scope end
    return;
  }
  worker_dict.insert({new_worker->get_emit_socket(), std::move(new_worker)});
}

std::unique_ptr<Worker> MasterState::pop_worker() {
  std::lock_guard<std::mutex> lock(worker_dict_lock);
  if (worker_dict.empty()) {
    throw std::runtime_error("No registered workers!");
  }

  // Find the worker with the lowest load, lazily delete inactive workers
  auto best = worker_dict.end();
  std::vector<WorkerDict::iterator> inactive_workers;

  for (auto iter = worker_dict.begin(); iter != worker_dict.end(); ++iter) {
    if (!iter->second->is_active()) {
      inactive_workers.push_back(iter);
      continue;
    }
    if (best == worker_dict.end() ||
        iter->second->load() < best->second->load()) {
      best = iter;
    }
  }

  for (auto it : inactive_workers) {
    LOG_INFO << "Lazy delete worker" << std::endl;
    worker_dict.erase(it);
  }
  // Handle case when all workers are inactive
  if (best == worker_dict.end()) {
    throw std::runtime_error("No active workers available!");
  }

  std::unique_ptr<Worker> to_return = std::move(best->second);
  worker_dict.erase(best);
  return to_return;
}

void MasterState::setup_job(const std::string& job_uuid,
                            const std::string& job_user,
                            const std::string& binary_path,
                            const std::string& mapper_name,
                            const std::string& reducer_name, int M, int R) {
  std::lock_guard<std::mutex> lock(master_lock);

  // store job metadata
  Job job(job_uuid, job_user, binary_path, mapper_name, reducer_name, M, R);
  job_metadata.insert({job_uuid, job});

  // push start job update to Eucalypt
  Persistor::get_instance()->start_job(
      StartJobEvent(job, time_utils::get_time()));
}

void MasterState::start_map_leg(const std::string& job_uuid,
                                const std::vector<nfs::fs::path>& job_files) {
  std::lock_guard<std::mutex> lock(master_lock);

  // set the current leg of the job as the map leg
  job_metadata.at(job_uuid).set_job_leg(JobLeg::Map);
  expected_tasks[job_uuid] = {};

  // init tasks belonging to this job_leg
  for (std::size_t i = 0; i < job_files.size(); i++) {
    Task task(job_uuid, job_files[i], i);
    std::string task_uuid = task.get_task_uuid();
    task_metadata.insert({task_uuid, task});
    expected_tasks[job_uuid].insert(task_uuid);
    pending_tasks.push_back(task_uuid);
  }

  // wake up the assign_tasks thread
  pending_tasks_semaphore.release();
}

void MasterState::start_reduce_leg(const std::string& job_uuid) {
  // the calling function holds the lock

  // set the current leg of the job as the map leg
  job_metadata.at(job_uuid).set_job_leg(JobLeg::Reduce);
  expected_tasks[job_uuid] = {};

  // init tasks belonging to this job_leg
  int r = job_metadata.at(job_uuid).get_R();
  for (int i = 0; i < r; i++) {
    Task task(job_uuid, std::optional<nfs::fs::path>(), i);
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

    LOG_INFO << "There are " << tasks_to_assign.size() << " tasks to assign\n";
    for (const auto& task_uuid : tasks_to_assign) {
      auto task = task_metadata.at(task_uuid);
      auto job = job_metadata.at(task.get_job_uuid());

      try {
        std::lock_guard<std::mutex> lock(
            master_lock);  // this portion needs to be atomic - otherwise acks and heartbeats will fail
        auto worker = pop_worker();

        worker->assign_work(job, task);

        // push start task update to Eucalypt
        Persistor::get_instance()->start_task(StartTaskEvent(
            task, time_utils::get_time(), worker->get_listen_socket()));

        push_worker(std::move(worker));
      } catch (std::exception& e) {
        LOG_ERROR << "An exception occurred while assigning task: " << e.what()
                  << '\n';
        // should probably re-insert the task in the pending list
      }
    }
  }
}

void MasterState::mark_task_as_finished(const Socket& worker_socket,
                                        const std::string& task_uuid) {
  std::lock_guard<std::mutex> lock(master_lock);

  // decrease worker load
  worker_dict.at(worker_socket)->finish_task(task_uuid);
  LOG_INFO << "Worker " << worker_dict.at(worker_socket)->address() << ':'
           << worker_dict.at(worker_socket)->listen_port() << " has "
           << worker_dict.at(worker_socket)->load() << " remaining load\n";

  // removes this task from the set of expected tasks for the current leg of the corresponding job
  auto task = task_metadata.at(task_uuid);
  auto job = job_metadata.at(task.get_job_uuid());
  auto job_uuid = job.get_job_uuid();
  expected_tasks[job_uuid].erase(task_uuid);
  task_metadata.erase(task_uuid);

  // push complete task update to Eucalypt
  long long ms = time_utils::get_time();
  Persistor::get_instance()->complete_event(
      CompleteEvent(CompleteEventType::TaskComplete, task_uuid, ms));

  // check if the current leg has finished
  if (expected_tasks[job_uuid].empty()) {
    LOG_INFO << "The " << job.get_current_leg() << " of the job " << job_uuid
             << " has finished!\n";

    if (job.get_current_leg() == JobLeg::Map) {
      start_reduce_leg(job_uuid);
    } else {
      // clean up job metadata
      job_metadata.erase(job_uuid);
      expected_tasks.erase(job_uuid);
      LOG_INFO << "Job " << job_uuid << " has finished. There are "
               << job_metadata.size() << " ongoing jobs\n";

      // push complete job update to Eucalypt
      Persistor::get_instance()->complete_event(
          CompleteEvent(CompleteEventType::JobComplete, job_uuid, ms));

      // notify user code
    }
  }
}

MasterState::~MasterState() {
  // terminate the thread that assigns pending tasks to workers
  run_assign_tasks_thread = false;
  pending_tasks_semaphore.release();
  assign_tasks_thread.join();
}
