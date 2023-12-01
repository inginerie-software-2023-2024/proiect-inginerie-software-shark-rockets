#include <gtest/gtest.h>
#include "map_reduce/src/utils.cpp"

TEST(SmokeTest, DoesNothing) {}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
