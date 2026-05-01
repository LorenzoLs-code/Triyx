cmake_minimum_required(VERSION 3.10)
project(Triyx)

set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE LEGACY)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(Triyx 
    src/main.cpp
    src/external/stb_image.cpp
)

target_include_directories(Triyx PRIVATE src/external)

target_link_libraries(Triyx 
    OpenGL::GL 
    GLEW::GLEW 
    /usr/lib/x86_64-linux-gnu/libglfw.so
)