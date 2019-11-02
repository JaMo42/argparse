cmake_minimum_required(VERSION 3.2)
# Build options
add_compile_options("-std=c++17" "-Wall")
# Set sources and include directories
file(GLOB LIB_SOURCES
    "source/*.cc"
)
file(GLOB TEST_SOURCES
    "test/*.cc"
)
include_directories(include)
# Create library
project(argparse VERSION 1.0 DESCRIPTION "C++ argument parser")
add_library(argparse SHARED ${LIB_SOURCES})
add_library(argparse_static ${LIB_SOURCES})
# Load google tests
enable_testing()
find_package(GTest MODULE REQUIRED)
# Create test program
project(argparse_test)
add_executable(argparse_test ${TEST_SOURCES})
set_target_properties(argparse_test PROPERTIES OUTPUT_NAME "test")
target_link_libraries(argparse_test PRIVATE GTest::GTest GTest::Main argparse)
add_test(AllTestsInMain argparse_test)
# Install
install(TARGETS argparse DESTINATION lib)
install(FILES "include/argparse.h" DESTINATION include)
