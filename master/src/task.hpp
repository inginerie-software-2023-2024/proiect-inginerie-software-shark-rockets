#pragma once
#include <string>
#include <vector>
#include "file_system_manager.hpp"
#include "utils.hpp"

class Task {
 private:
  std::string task_uuid, job_uuid;
  std::vector<nfs::fs::path> job_input_files;

 public:
  Task(std::string job_uuid, const std::vector<nfs::fs::path>& job_input_files)
      : task_uuid(uuid::generate_uuid()),
        job_uuid(job_uuid),
        job_input_files(job_input_files){};

  std::string get_task_uuid() const { return task_uuid; }

  std::string get_job_uuid() const { return job_uuid; }

  std::vector<nfs::fs::path> get_job_input_files() const {
    return job_input_files;
  }
};
