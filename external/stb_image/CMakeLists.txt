cmake_minimum_required(VERSION 3.0)
project(StbImage)

add_library(stb_image src/stb_image.cpp)
target_include_directories(stb_image PUBLIC include)