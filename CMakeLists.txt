cmake_minimum_required(VERSION 3.6)
project(TSP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Point.cpp Point.h Gen.cpp)
add_executable(TSP ${SOURCE_FILES})