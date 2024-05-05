cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cubes cubes.cpp)
target_link_libraries(cubes PRIVATE ScratchRenderer)
target_include_directories(cubes PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src ${CMAKE_CURRENT_SOURCE_DIR}/../extern/glm)

add_executable(pyramid_gradient pyramid_gradient.cpp)
target_link_libraries(pyramid_gradient PRIVATE ScratchRenderer sfml-graphics)
target_include_directories(pyramid_gradient PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src ${CMAKE_CURRENT_SOURCE_DIR}/../extern/glm)

add_executable(load_model load_model.cpp)
target_link_libraries(load_model PRIVATE ScratchRenderer)
target_include_directories(load_model PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src ${CMAKE_CURRENT_SOURCE_DIR}/../extern/glm)