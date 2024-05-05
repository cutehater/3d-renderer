cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
)
FetchContent_MakeAvailable(googletest)

add_executable(ScratchRendererTests 
unit_main.cpp 
unit_vector4.cpp 
unit_vertex.cpp 
unit_triangle.cpp 
unit_object.cpp 
unit_world.cpp 
unit_storage2d.cpp 
unit_screen.cpp)
target_link_libraries(ScratchRendererTests gtest gtest_main ScratchRenderer sfml-graphics)
target_include_directories(ScratchRendererTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src ${CMAKE_CURRENT_SOURCE_DIR}/../extern/glm)

include(GoogleTest)
gtest_discover_tests(ScratchRendererTests)