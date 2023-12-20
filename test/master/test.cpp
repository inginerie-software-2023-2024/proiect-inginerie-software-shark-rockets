#include <gtest/gtest.h>
#include "job_wait_test.cpp"
#include "nfs_test.cpp"

TEST(SmokeTest, DoesNothing) {}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
