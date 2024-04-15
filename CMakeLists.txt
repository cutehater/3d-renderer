cmake_minimum_required(VERSION 3.15)
project(ScratchRenderer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(extern)
add_subdirectory(src)

target_link_libraries(
    sfml-graphics
    sfml-window
    sfml-system
)