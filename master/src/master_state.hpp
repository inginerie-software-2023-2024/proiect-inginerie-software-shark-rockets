#pragma once
#include <grpcpp/grpcpp.h>
#include <atomic>
#include <mutex>
#include <queue>
#include <semaphore>
#include <thread>
#include "file_system_manager.hpp"
#include "job.hpp"
#include "persistor.hpp"
#include "task.hpp"
#include "worker.hpp"

class MasterState {
 private:
  // Worker info
  // The key is the socket from which a worker initiates all comunication with the master
  // The value is a unique_ptr to worker wrapper
  // This representation is useful for worker acks and heartbeats
  WorkerDict worker_dict;

  // Job info
  std::unordered_map<std::string, Job> job_metadata;  // metadata of a job
  std::unordered_map<std::string, std::unordered_set<std::string>>
      expected_tasks;  // unfinished tasks for the current leg of a job

  // Task info
  std::unordered_map<std::string, Task> task_metadata;  // metadata of a task
  std::vector<std::string> pending_tasks;

  // Thread that assigns tasks to workers
  std::thread assign_tasks_thread;

  // Sync primitives
  std::mutex master_lock;
  std::counting_semaphore<> pending_tasks_semaphore;
  std::atomic_bool run_assign_tasks_thread;

 public:
  MasterState();
  void create_worker(const std::string& addr, const int listen_port,
                     const int emit_port);

  // Moves a new worker into the data structure, transferring ownership.
  void push_worker(std::unique_ptr<Worker> new_worker);

  // Pops the worker with the smallest load and returns ownership to the caller.
  std::unique_ptr<Worker> pop_worker();

  // Stores the necessary job, map-leg and reduce-leg metadata.
  void setup_job(const std::string& job_uuid, const std::string& job_user,
                 const std::string& binary_path, const std::string& mapper_name,
                 const std::string& reducer_name, int M, int R);

  // Starts the map leg for a given job.
  void start_map_leg(const std::string& job_uuid,
                     const std::vector<nfs::fs::path>& input_files);

  // Starts the reduce leg for a given job.
  void start_reduce_leg(const std::string& job_uuid);

  // Decreases the load of the worker.
  // Deletes this task from the set of expected tasks for the current leg of the corresponding job.
  // Checks if the current leg of the corresponding job has finished.
  void mark_task_as_finished(const Socket& worker_socket,
                             const std::string& task_uuid);

  // Periodically assign pending tasks to workers
  void assign_tasks();

  ~MasterState();
};
