cmake_minimum_required(VERSION 3.13)
project(AlgTraining)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")

#add_executable(LongestCommonSequence lcs.cpp)
add_executable(algorithms2019 main.cpp)
