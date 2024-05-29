cmake_minimum_required(VERSION 3.15)
project(ScratchRenderer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_subdirectory(extern/glm)
add_subdirectory(src)

if (EXAMPLES)
    add_subdirectory(examples)
endif()

if (TEST)
    add_subdirectory(test)
endif()
