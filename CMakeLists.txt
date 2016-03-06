cmake_minimum_required(VERSION 3.3)
project(leetcode)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O2 -pthread")

add_executable(1_Two_Sum 1_Two_Sum/TwoSum.cpp)