cmake_minimum_required(VERSION 3.10)
project(Triyx)
set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE LEGACY)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_executable(Triyx 
    src/main.cpp
    src/rendering/rendering.cpp
    src/external/stb_image.cpp
)

target_include_directories(Triyx PRIVATE src/external src)

target_link_libraries(Triyx 
    OpenGL::GL 
    GLEW::GLEW 
    glm::glm
    /usr/lib/x86_64-linux-gnu/libglfw.so
)