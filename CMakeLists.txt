cmake_minimum_required(VERSION 3.15)
project(ScratchRendererApplication)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_subdirectory(extern/glm)
add_subdirectory(src)
add_subdirectory(examples)
