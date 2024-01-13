// To generate data, see sandbox/data/real_estate.py

#include <unistd.h>
#include <chrono>
#include <iostream>
#include "koala.hpp"

class CSVParser : public map_reduce::Mapper {
 public:
  void map(const std::string& line) {
    // CSV line format: address,num_bedrooms,price
    // Assume deal is good if num_bedrooms * 20000 > price

    std::size_t first_comma = line.find(",");
    std::size_t second_comma = line.find(",", first_comma + 1);

    int num_bedrooms =
        std::stoi(line.substr(first_comma + 1, second_comma - first_comma - 1));
    int price = std::stoi(
        line.substr(second_comma + 1, (int)line.size() - second_comma - 1));

    if (num_bedrooms * 20000 > price)
      emit(line, "");
  }
};
REGISTER_MAPPER(CSVParser);

class Identity : public map_reduce::Reducer {
 public:
  void reduce(const std::string& key, map_reduce::ValueIterator& iter) {
    // do not alter kvs
    while (iter.has_next())
      emit(key, iter.get());
  }
};
REGISTER_REDUCER(Identity);

int main(int argc, char** argv) {
  // Init should be called after all mappers and reducers are registered
  // It sets up the connection to the master node
  // It checks whether or not this process should run in user mode, mapper mode, reducer mode ...
  map_reduce::init(argc, argv);

  // We submit a job to be computed
  auto job = map_reduce::register_job("CSVParser", "Identity",
                                      "^real_estate/.*.txt$", 1);

  auto start = std::chrono::system_clock::now();
  map_reduce::join_job(job);
  auto end = std::chrono::system_clock::now();

  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Job finished, took: " << elapsed.count() << " ms" << std::endl;
  return 0;
}
