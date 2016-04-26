cmake_minimum_required(VERSION 3.5)
project(machine_learning)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c)
add_executable(machine_learning ${SOURCE_FILES})
add_library(machine_learning_library SHARED ${SOURCE_FILES})