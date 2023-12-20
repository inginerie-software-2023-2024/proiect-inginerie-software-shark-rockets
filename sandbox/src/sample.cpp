#include <unistd.h>
#include <iostream>
#include "koala.hpp"

// User's mapper function
class MyMapper : public map_reduce::Mapper {
 public:
  void map(const std::string& line) {
    // for each line, emit it's length and 1
    // in the reducer, we should sum up all the 1s for a given key, s.t. we'll have a frequency map of line lengths
    emit(std::to_string(line.size()), std::to_string(1));
  }
};
REGISTER_MAPPER(MyMapper);

// User's reducer function
class MyReducer : public map_reduce::Reducer {
 public:
  void reduce() {
    std::cout << "Hello from reduce function!\n";
    sleep(7);
    std::cout << "Reduce function finished!\n";
  }
};
REGISTER_REDUCER(MyReducer);

int main(int argc, char** argv) {
  // Init should be called after all mappers and reducers are registered
  // It sets up the connection to the master node
  // It checks whether or not this process should run in user mode, mapper mode, reducer mode ...
  map_reduce::init(argc, argv);

  // We submit a job to be computed
  map_reduce::register_job("MyMapper", "MyReducer", "^.*.txt$", 5, "dimi0402@yahoo.com", "6582ba59f359ed9f7b35247a");

  return 0;
}
