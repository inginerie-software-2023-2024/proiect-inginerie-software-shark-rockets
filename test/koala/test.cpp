#include <gtest/gtest.h>

TEST(SmokeTest, DoesNothing) {}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
