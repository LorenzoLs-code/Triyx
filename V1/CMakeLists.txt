cmake_minimum_required(VERSION 3.10)
project(LittleStar)

set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE LEGACY)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(LittleStar src/main.cpp)

target_link_libraries(LittleStar 
    OpenGL::GL 
    GLEW::GLEW 
    /usr/lib/x86_64-linux-gnu/libglfw.so
)