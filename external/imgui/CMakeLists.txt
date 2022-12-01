cmake_minimum_required(VERSION 3.0)
project(Imgui)

find_package(glfw3 REQUIRED)

add_library(imgui
    imgui.cpp
    imgui.h
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_internal.h
    imgui_widgets.cpp
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
    imconfig.h
    imgui_tables.cpp
    backends/imgui_impl_glfw.h
    backends/imgui_impl_glfw.cpp
    backends/imgui_impl_opengl3.h
    backends/imgui_impl_opengl3.cpp
    )
target_include_directories(imgui PUBLIC .)
target_link_libraries(imgui glfw)