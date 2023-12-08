#pragma once
#include <string>

enum JobLeg { MapLeg, ReduceLeg };

class Job {
 private:
  std::string job_uuid, job_user, binary_path, mapper_name, reducer_name;

 public:
  Job(const std::string& job_uuid, const std::string& job_user,
      const std::string& binary_path, const std::string& mapper_name,
      const std::string& reducer_name)
      : job_uuid(job_uuid),
        job_user(job_user),
        binary_path(binary_path),
        mapper_name(mapper_name),
        reducer_name(reducer_name){};

  std::string get_job_uuid() { return job_uuid; }

  std::string get_job_user() { return job_user; }

  std::string get_binary_path() { return binary_path; }

  std::string get_exec_class(JobLeg job_leg) {
    if (job_leg == JobLeg::MapLeg)
      return mapper_name;
    return reducer_name;
  }
};
