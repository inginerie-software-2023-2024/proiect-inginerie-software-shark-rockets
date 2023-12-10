#pragma once
#include <ostream>

enum JobLeg { Init, Map, Reduce };

inline std::ostream& operator<<(std::ostream& os, const JobLeg& job_leg) {
  switch (job_leg) {
    case JobLeg::Init:
      os << "[job is in init state - no leg has begun]";
      break;

    case JobLeg::Map:
      os << "map leg";
      break;

    case JobLeg::Reduce:
      os << "reduce leg";
      break;
  }

  return os;
}
