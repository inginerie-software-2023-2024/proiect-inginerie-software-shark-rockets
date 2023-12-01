find_package(GTest REQUIRED)

set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/package/test")

add_subdirectory(master)
add_subdirectory(worker)
add_subdirectory(koala)

add_test(NAME MasterTests COMMAND test_master)
add_test(NAME WorkerTests COMMAND test_master)
add_test(NAME KoalaTests COMMAND test_koala)
