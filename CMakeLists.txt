cmake_minimum_required(VERSION 3.5)
project(machine_learning)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(SOURCE_FILES main.cpp)
#add_executable(machine_learning ${SOURCE_FILES} main.cpp)
add_library(machine_learning SHARED ${SOURCE_FILES})