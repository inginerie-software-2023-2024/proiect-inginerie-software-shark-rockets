#include <unistd.h>
#include <chrono>
#include <iostream>
#include "koala.hpp"

// User's mapper function
class MyMapper : public map_reduce::Mapper {
 public:
  void map(const std::string& line) {
    // for each line, emit it's length and 1
    // in the reducer, we should sum up all the 1s for a given key, s.t. we'll have a frequency map of line lengths
    std::cout << line << std::endl;
    emit(std::to_string(line.size()), std::to_string(1));
  }
};
REGISTER_MAPPER(MyMapper);

// User's reducer function
class MyReducer : public map_reduce::Reducer {
 public:
  void reduce(const std::string& key, map_reduce::ValueIterator& iter) {
    // calculate frequency for a given line length
    int sum = 0;
    while (iter.has_next()) {
      sum += std::stoi(iter.get());
    }

    std::cout << key << ' ' << sum << std::endl;
    emit(key, std::to_string(sum));
  }
};
REGISTER_REDUCER(MyReducer);

int main(int argc, char** argv) {
  // Init should be called after all mappers and reducers are registered
  // It sets up the connection to the master node
  // It checks whether or not this process should run in user mode, mapper mode, reducer mode ...
  map_reduce::init(argc, argv);

  // We submit a job to be computed
  auto job =
      map_reduce::register_job("MyMapper", "MyReducer", "^.*.txt$", 5, "65abeb4e54f997c0fad86385");

  auto start = std::chrono::system_clock::now();
  map_reduce::join_job(job);
  auto end = std::chrono::system_clock::now();

  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Job finished, took: " << elapsed.count() << " ms" << std::endl;
  return 0;
}
