cmake_minimum_required(VERSION 3.6)
project(FillwordsSolver)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/Trie.hpp src/Nodes/ListNode.cpp src/Nodes/ArrayNode.cpp src/Nodes/ArrayNode.h src/Nodes/AbstractNode.h src/Solver.cpp src/Nodes/HashNode.cpp src/Nodes/STL_ArrayNode.cpp src/Nodes/STL_ArrayNode.h src/Utilities.cpp src/Nodes/TestListNode.cpp src/Nodes/TestListNode.h)
#set(SOURCE_FILES main.cpp src)
add_executable(FillwordsSolver ${SOURCE_FILES})