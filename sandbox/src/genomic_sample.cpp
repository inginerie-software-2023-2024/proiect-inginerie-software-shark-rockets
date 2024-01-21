#include <unistd.h>
#include <iostream>
#include <string>
#include <chrono>
#include "koala.hpp"

// Function to check if the pattern exists in the line
bool containsPattern(const std::string& line, const std::string& pattern) {
    return line.find(pattern) != std::string::npos;
}

// User's mapper function
class GenomicMapper : public map_reduce::Mapper {
public:
    void map(const std::string& line) {
        const std::string pattern = "ATCGGCATCCT"; // Example pattern
        // find number of occurrences of pattern in line
        int count = 0;
        for (int i = 0; i < (int)line.size() - (int)pattern.size() + 1; i++) {
            if (containsPattern(line.substr(i, pattern.size()), pattern)) {
                count++;
            }
        }
        emit(line, std::to_string(count));
    }
};
REGISTER_MAPPER(GenomicMapper);

// User's reducer function
class GenomicReducer : public map_reduce::Reducer {
public:
    void reduce(const std::string& key, map_reduce::ValueIterator& iter) {
        int count = 0;
        while (iter.has_next()) {
            count += std::stoi(iter.get());
        }
        std::cout << key << ": " << count << std::endl;
        emit(key, std::to_string(count));
    }
};
REGISTER_REDUCER(GenomicReducer);

int main(int argc, char** argv) {
    map_reduce::init(argc, argv);

    // We submit a job to be computed
    auto job = map_reduce::register_job("GenomicMapper", "GenomicReducer", 
                                "^.*.csv$", 1);

    auto start = std::chrono::system_clock::now();
    map_reduce::join_job(job);
    auto end = std::chrono::system_clock::now();

    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Job finished, took: " << elapsed.count() << " ms" << std::endl;
    return 0;
}
