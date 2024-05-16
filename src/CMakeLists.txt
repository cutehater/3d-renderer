cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ScratchRenderer STATIC
    application.cpp
    camera.cpp
    object.cpp
    off_loader.cpp
    primitives.cpp
    renderer.cpp
    screen.cpp
    vector4.cpp
    world.cpp
)

target_link_libraries(ScratchRenderer PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

target_include_directories(ScratchRenderer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../extern/glm)
