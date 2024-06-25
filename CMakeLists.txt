project(xgraph_project)
cmake_minimum_required(VERSION 3.22)

set(BIN_DIR ${xgraph_project_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11 -ggdb")

add_subdirectory(app)
