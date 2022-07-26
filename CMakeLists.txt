cmake_minimum_required(VERSION 3.14)
project(cart)
set(CMAKE_CXX_STANDARD 14) # for gtest
find_package(Eigen3 REQUIRED)
find_package(GTest REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${GTEST_INCLUDE_DIR})

add_library(cart
  src/io.cc  
  src/real_time_scan_matcher_2d.cc
)

add_executable(real_time_scan_matcher_2d_test src/real_time_scan_matcher_2d_test.cc)
target_link_libraries(real_time_scan_matcher_2d_test cart ${GTEST_LIBRARIES} pthread)

add_executable(main src/main.cc)