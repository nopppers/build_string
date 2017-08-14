cmake_minimum_required(VERSION 2.6)

project(build_string)


add_executable(build_string_test build_string.hpp test/build_string_test.cpp)

target_include_directories(build_string_test PRIVATE ${CMAKE_SOURCE_DIR}/test/dep/)
target_include_directories(build_string_test PRIVATE ${CMAKE_SOURCE_DIR})
