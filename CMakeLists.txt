cmake_minimum_required(VERSION 3.15)
project(ScratchRenderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(extern)
add_subdirectory(include)
add_subdirectory(src)