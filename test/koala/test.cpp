#include <gtest/gtest.h>
#include "lib_test.cpp"

TEST(SmokeTest, DoesNothing) {}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
