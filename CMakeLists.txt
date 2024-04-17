cmake_minimum_required(VERSION 3.15)
project(ScratchRenderer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app
    main.cpp
    src/application.cpp
    src/camera.cpp
    src/object.cpp
    src/primitives.cpp
    src/renderer.cpp
    src/screen.cpp
    src/vector4.cpp
    src/world.cpp
)

target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/extern)

target_link_libraries(
    sfml-graphics
    sfml-window
    sfml-system
)