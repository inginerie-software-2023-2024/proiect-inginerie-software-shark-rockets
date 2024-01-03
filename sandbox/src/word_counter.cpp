#include <unistd.h>
#include <chrono>
#include <iostream>
#include <vector>
#include "koala.hpp"

class WordSplitter : public map_reduce::Mapper {
 public:
  void map(const std::string& line) {
    // for each word w, emit (w, 1)

    // spaces, punctuation etc.
    std::vector<int> v;
    for (int i = 0; i < (int)line.size(); i++)
      if (!isalnum(line[i]))
        v.push_back(i);
    v.push_back(line.size());

    if (v[0] > 0)
      emit(line.substr(0, v[0]), std::to_string(1));
    for (int i = 0; i < (int)v.size() - 1; i++) {
      if (v[i + 1] - v[i] - 1 > 0)
        emit(line.substr(v[i] + 1, v[i + 1] - v[i] - 1), std::to_string(1));
    }
  }
};
REGISTER_MAPPER(WordSplitter);

class Counter : public map_reduce::Reducer {
 public:
  void reduce(const std::string& key, map_reduce::ValueIterator& iter) {
    // calculate frequency for a given word
    int sum = 0;
    while (iter.has_next()) {
      auto res = iter.get();
      sum += std::stoi(res);
    }

    std::cout << key << ' ' << sum << std::endl;
    emit(key, std::to_string(sum));
  }
};
REGISTER_REDUCER(Counter);

int main(int argc, char** argv) {
  // Init should be called after all mappers and reducers are registered
  // It sets up the connection to the master node
  // It checks whether or not this process should run in user mode, mapper mode, reducer mode ...
  map_reduce::init(argc, argv);

  // We submit a job to be computed
  auto job =
      map_reduce::register_job("WordSplitter", "Counter", "^lorem/.*.txt$", 5);

  auto start = std::chrono::system_clock::now();
  map_reduce::join_job(job);
  auto end = std::chrono::system_clock::now();

  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Job finished, took: " << elapsed.count() << " ms" << std::endl;
  return 0;
}
