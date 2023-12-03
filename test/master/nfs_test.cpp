#include <gtest/gtest.h>
#include "master/src/file_system_manager.cpp"
#include "master/src/user.cpp"
#include "master/src/utils.cpp"

namespace nfs {
class FileSystemTest : public ::testing::Test {
 protected:
  fs::path temp_dir_path;

  void SetUp() override {
    temp_dir_path = fs::temp_directory_path() / "gtest_ensure_directory_test";
    fs::create_directory(temp_dir_path);
  }

  void TearDown() override { fs::remove_all(temp_dir_path); }
};
TEST_F(FileSystemTest, DirectoryExists) {
  fs::path sub_dir = temp_dir_path / "subdir";
  fs::create_directory(sub_dir);
  EXPECT_TRUE(ensure_directory(sub_dir));
}

TEST_F(FileSystemTest, PathExistsButIsNotDirectory) {
  fs::path file_path = temp_dir_path / "file.txt";
  std::ofstream(file_path.string()) << "Test file content";
  EXPECT_FALSE(ensure_directory(file_path));
}

TEST_F(FileSystemTest, DirectoryDoesNotExist) {
  fs::path new_dir = temp_dir_path / "new_dir";
  EXPECT_TRUE(ensure_directory(new_dir));
  EXPECT_TRUE(fs::exists(new_dir) && fs::is_directory(new_dir));
}

class FileSystemPatternTest : public ::testing::Test {
 protected:
  fs::path temp_dir_path;

  void SetUp() override {
    temp_dir_path =
        fs::temp_directory_path() / "gtest_list_files_matching_pattern_test";
    fs::create_directory(temp_dir_path);

    std::ofstream(temp_dir_path / "file1.txt");
    std::ofstream(temp_dir_path / "file2.txt");
    std::ofstream(temp_dir_path / "document.pdf");
    fs::create_directory(temp_dir_path / "subdir");
    std::ofstream(temp_dir_path / "subdir" / "file3.txt");
  }

  void TearDown() override { fs::remove_all(temp_dir_path); }
};

TEST_F(FileSystemPatternTest, MatchingFiles) {
  auto matching_files =
      list_files_matching_pattern(temp_dir_path, "^.*\\.txt$");
  EXPECT_EQ(matching_files.size(), 3);
}

TEST_F(FileSystemPatternTest, NoMatchingFiles) {
  auto matching_files =
      list_files_matching_pattern(temp_dir_path, "^.*\\.doc$");
  EXPECT_TRUE(matching_files.empty());
}

TEST_F(FileSystemPatternTest, InvalidBasePath) {
  auto matching_files = list_files_matching_pattern(
      temp_dir_path / "non_existent_dir", "^.*\\.txt$");
  EXPECT_TRUE(matching_files.empty());
}

TEST_F(FileSystemPatternTest, ComplexPatterns) {
  auto matching_files =
      list_files_matching_pattern(temp_dir_path, "^file.{1}\\.txt$");
  EXPECT_EQ(matching_files.size(), 2);
}

class JobStructureTest : public ::testing::Test {
 protected:
  fs::path temp_dir_path;

  void SetUp() override {
    temp_dir_path =
        fs::temp_directory_path() / "gtest_create_job_structure_test";
    fs::create_directory(temp_dir_path);
  }

  void TearDown() override { fs::remove_all(temp_dir_path); }
};

TEST_F(JobStructureTest, SuccessfulCreation) {
  fs::path job_root = temp_dir_path / "job";
  fs::create_directories(job_root);
  ASSERT_TRUE(create_job_structure(job_root));
  for (const auto& job_dir : {"input", "intermediary", "output"}) {
    EXPECT_TRUE(fs::exists(job_root / job_dir));
    EXPECT_TRUE(fs::is_directory(job_root / job_dir));
  }
}

TEST_F(JobStructureTest, ExistingJobStructure) {
  fs::path job_root = temp_dir_path / "existing_job";
  fs::create_directories(job_root / "input");
  fs::create_directories(job_root / "intermediary");
  fs::create_directories(job_root / "output");
  EXPECT_TRUE(create_job_structure(job_root));
}

TEST_F(JobStructureTest, InvalidRootDirectory) {
  fs::path invalid_root = "/invalid_path";
  EXPECT_FALSE(create_job_structure(invalid_root));
}

class SymLinkDataTest : public ::testing::Test {
 protected:
  fs::path temp_dir_path;
  std::vector<fs::path> test_files;

  void SetUp() override {
    temp_dir_path = fs::temp_directory_path() / "gtest_sym_link_data_test";
    fs::create_directories(temp_dir_path / "input");

    for (int i = 0; i < 3; ++i) {
      fs::path file_path =
          temp_dir_path / ("file" + std::to_string(i) + ".txt");
      std::ofstream(file_path) << "Sample content " << i;
      test_files.push_back(file_path);
    }
  }

  void TearDown() override { fs::remove_all(temp_dir_path); }
};

TEST_F(SymLinkDataTest, SuccessfulSymlinkCreation) {
  auto linked_files = sym_link_data(test_files, temp_dir_path);
  EXPECT_EQ(linked_files.size(), test_files.size());

  for (size_t i = 0; i < linked_files.size(); ++i) {
    EXPECT_TRUE(fs::exists(linked_files[i]));
    EXPECT_TRUE(fs::is_symlink(linked_files[i]));
    fs::path expected_target =
        fs::relative(test_files[i], temp_dir_path / "input");
    EXPECT_EQ(fs::read_symlink(linked_files[i]), expected_target);
  }
}

TEST_F(SymLinkDataTest, NonExistentFiles) {
  std::vector<fs::path> non_existent_files = {temp_dir_path /
                                              "nonexistent.txt"};
  EXPECT_THROW(sym_link_data(non_existent_files, temp_dir_path),
               fs::filesystem_error);
}

TEST_F(SymLinkDataTest, InvalidJobRoot) {
  fs::path invalid_root = "/invalid_path";
  std::vector<fs::path> valid_files = {temp_dir_path / "file0.txt"};
  EXPECT_THROW(sym_link_data(valid_files, invalid_root), fs::filesystem_error);
}

TEST_F(SymLinkDataTest, EmptyFileList) {
  std::vector<fs::path> empty_file_list;
  auto linked_files = sym_link_data(empty_file_list, temp_dir_path);
  EXPECT_TRUE(linked_files.empty());
}
}  // namespace nfs
