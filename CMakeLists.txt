cmake_minimum_required(VERSION 3.2)
# Build options
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -DDEBUG")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
add_compile_options("-std=c++17" "-Wall")
# Set sources and include directories
file(GLOB SOURCES
    "source/*.cc"
)
include_directories(include)
# Create library
project(argparse)
add_library(argparse ${SOURCES})
# Load google tests
enable_testing()
find_package(GTest MODULE REQUIRED)
# Create test program
project(argparse_test)
add_executable(argparse_test "test/test.cc")
set_target_properties(argparse_test PROPERTIES OUTPUT_NAME "test")
target_link_libraries(argparse_test PRIVATE GTest::GTest GTest::Main argparse)
add_test(AllTestsInMain argparse_test)
