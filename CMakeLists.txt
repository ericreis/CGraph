cmake_minimum_required(VERSION 3.3)
project(CGraph)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Graph.cpp Graph.h AdjacencyMatrix.cpp AdjacencyMatrix.h Constants.cpp Constants.h AdjacencyVector.cpp AdjacencyVector.h)
add_executable(CGraph ${SOURCE_FILES})