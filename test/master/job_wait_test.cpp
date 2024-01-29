#include <gtest/gtest.h>
#include <chrono>
#include <future>
#include "master/src/job_wait_handle.cpp"
using namespace std::chrono_literals;

TEST(JobWaitTest, WorkerIsBlockedUntilFinish) {
  JobWaitHandle handle;

  // Create a worker that waits for the job to finish.
  std::future<void> future = std::async([&handle] { handle.wait(); });

  auto status = future.wait_for(100ms);
  ASSERT_EQ(status, std::future_status::timeout);

  handle.set_finished();
  status = future.wait_for(100ms);
  ASSERT_EQ(status, std::future_status::ready);
}

TEST(JobWaitTest, WaitAfterFinishNotBlocking) {
  JobWaitHandle handle;
  handle.set_finished();

  std::future<void> future = std::async([&handle] { handle.wait(); });
  auto status = future.wait_for(100ms);
  ASSERT_EQ(status, std::future_status::ready);
}

TEST(JobWaitTest, AllWorkersAreBlockedUntilFinish) {
  JobWaitHandle handle;

  // Create a bunch of workers that wait for the job completion.
  std::vector<std::future<void>> futures;
  for (int i = 0; i < 5; i++) {
    futures.push_back(std::async([&handle] { handle.wait(); }));
  }

  // They should be blocked.
  for (const auto& f : futures) {
    auto status = f.wait_for(100ms);
    ASSERT_EQ(status, std::future_status::timeout);
  }
  handle.set_finished();

  // Then they should all be released.
  for (const auto& f : futures) {
    auto status = f.wait_for(100ms);
    ASSERT_EQ(status, std::future_status::ready);
  }
}