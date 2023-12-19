#pragma once
#include <stdexcept>
#include <string>
#include "job_leg.hpp"

class Job {
 private:
  std::string job_uuid, job_user, binary_path, mapper_name, reducer_name;
  int M_, R_;
  JobLeg current_leg;

 public:
  Job(const std::string& job_uuid, const std::string& job_user,
      const std::string& binary_path, const std::string& mapper_name,
      const std::string& reducer_name, int M, int R)
      : job_uuid(job_uuid),
        job_user(job_user),
        binary_path(binary_path),
        mapper_name(mapper_name),
        reducer_name(reducer_name),
        M_(M),
        R_(R),
        current_leg(JobLeg::Init){};

  std::string get_job_uuid() const { return job_uuid; }

  std::string get_job_user() const { return job_user; }

  std::string get_binary_path() const { return binary_path; }

  std::string get_mapper_name() const { return mapper_name; }

  std::string get_reducer_name() const { return reducer_name; }

  std::string get_exec_class() const {
    if (current_leg == JobLeg::Init) {
      throw std::runtime_error("Job did not initialize any leg!");
    }
    if (current_leg == JobLeg::Map)
      return mapper_name;
    return reducer_name;
  }

  int get_M() const { return M_; }

  int get_R() const { return R_; }

  JobLeg get_current_leg() const { return current_leg; }

  void set_job_leg(JobLeg job_leg) { current_leg = job_leg; }
};
