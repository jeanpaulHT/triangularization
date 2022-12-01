cmake_minimum_required(VERSION 3.16.3)
project(Superficie)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)
add_subdirectory(external)

add_executable(Superficie basic_lighting_diffuse.cpp)

target_compile_definitions(Superficie PRIVATE GLFW_INCLUDE_NONE)
target_compile_options(Superficie PRIVATE  -Wall -Wextra -Wpedantic)
target_link_libraries(Superficie PRIVATE OpenGL::GL OpenGL::GLU glfw glad assimp stb_image imgui glm::glm dl)