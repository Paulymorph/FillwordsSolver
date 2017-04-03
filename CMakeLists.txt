cmake_minimum_required(VERSION 3.6)
project(FillwordsSolver)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Trie.cpp Trie.h Node.cpp Node.h Edge.cpp Edge.h)
add_executable(FillwordsSolver ${SOURCE_FILES})