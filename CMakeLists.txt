cmake_minimum_required(VERSION 3.27)

project(begonia)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER clang++)

add_subdirectory(server)
add_subdirectory(client)
