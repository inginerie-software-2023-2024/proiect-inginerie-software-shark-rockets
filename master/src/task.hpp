#pragma once
#include <optional>
#include <string>
#include <vector>
#include "file_system_manager.hpp"
#include "utils.hpp"

class Task {
 private:
  std::string task_uuid, job_uuid;
  std::optional<nfs::fs::path> task_input_file;
  int idx_;

 public:
  Task(std::string job_uuid,
       const std::optional<nfs::fs::path>& task_input_file, int idx)
      : task_uuid(uuid::generate_uuid()),
        job_uuid(job_uuid),
        task_input_file(task_input_file),
        idx_(idx){};

  std::string get_task_uuid() const { return task_uuid; }

  std::string get_job_uuid() const { return job_uuid; }

  std::optional<nfs::fs::path> get_task_input_file() const {
    return task_input_file;
  }

  int get_idx() const { return idx_; }
};
