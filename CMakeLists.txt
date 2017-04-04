cmake_minimum_required(VERSION 3.6)
project(FillwordsSolver)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Trie.hpp ListNode.cpp ArrayNode.cpp ArrayNode.h AbstractNode.h Solver.cpp)
add_executable(FillwordsSolver ${SOURCE_FILES})