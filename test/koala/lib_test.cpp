#include <gtest/gtest.h>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include "map_reduce/src/map_reduce.cpp"
#include "map_reduce/src/utils.cpp"

TEST(MapperTest, RetrieveEmittedValues) {
  class MyMapper : public map_reduce::Mapper {
    void map(const std::string& line) {
      // emit the number of characters read
      emit(std::to_string(line.size()), "");
    }
  };

  std::unique_ptr<map_reduce::Mapper> my_mapper = std::make_unique<MyMapper>();

  map_reduce::KVs kvs;
  my_mapper->pImpl->set_drain(&kvs);

  // feed the mapper with 100 strings of length 1, 2, ..., 100 respectively
  for (int i = 1; i <= 100; i++) {
    std::string s;
    for (int j = 0; j < i; j++)
      s += '1';
    my_mapper->map(s);
  }

  // expect that the mapper emitted values 1, 2, ..., 100
  ASSERT_EQ(kvs.size(), 100);

  std::multiset<std::pair<std::string, std::string>> expected;
  for (int i = 1; i <= 100; i++)
    expected.insert({std::to_string(i), ""});

  ASSERT_EQ(kvs, expected);
}

TEST(ReducerTest, TestKVManager) {
  // File 1: (A 1) (B 1) (B 2)
  // File 2: (A 2) (A 3) (A 4)
  // File 3: (A 5) (B 3) (C 1)

  // Expected for A: {1, 2, 3, 4, 5}
  // Expected for B: {1, 2, 3}
  // Expected for C: {1}

  namespace fs = boost::filesystem;

  fs::ofstream file_1("1"), file_2("2"), file_3("3");
  file_1 << "A 1\nB 1\nB 2\n";
  file_2 << "A 2\nA 3\nA 4\n";
  file_3 << "A 5\nB 3\nC 1\n";
  file_1.close();
  file_2.close();
  file_3.close();

  map_reduce::KVManager kv_manager(
      {fs::path("1"), fs::path("2"), fs::path("3")});

  std::unordered_map<std::string, std::unordered_set<std::string>> expected_for;
  expected_for["A"] = {"1", "2", "3", "4", "5"};
  expected_for["B"] = {"1", "2", "3"};
  expected_for["C"] = {"1"};

  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(kv_manager.has_next_key(), true);

    std::string current_key = kv_manager.get_next_key().value();
    EXPECT_EQ(current_key, std::string(1, 'A' + i));

    auto iter =
        map_reduce::ValueIterator(current_key, [&kv_manager, &current_key]() {
          return kv_manager.get_value_for_key(current_key);
        });

    std::unordered_set<std::string> values;
    while (iter.has_next())
      values.insert(iter.get());

    EXPECT_EQ(values, expected_for[current_key]);
  }

  EXPECT_EQ(kv_manager.has_next_key(), false);

  // cleanup
  fs::remove(fs::path("1"));
  fs::remove(fs::path("2"));
  fs::remove(fs::path("3"));
}
