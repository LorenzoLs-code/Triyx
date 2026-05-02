#include <GL/glew.h> // for rendendering whats in the window
#include <GLFW/glfw3.h> // for makeing a window
#include "external/stb_image.h" // for reading textures 

#include "rendering/rendering.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    glfwInit(); // initialize GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "Triyx", NULL, NULL); // Create a window
    glfwMakeContextCurrent(window); // show the window
    rendering render;
    glEnable(GL_DEPTH_TEST);
    
    /* ======
        Cube
       ====== */
    rendering::object cube;

    // Help func - create Point
    auto p = [](float x, float y, float z, float u, float v) {
        return rendering::verticesPoint{x, y, z, u, v};
    };

    // 8 corners of the cube, each side as 2 triangles
    // Front (z = +0.5)
    cube.triangles.push_back({ p(-0.5f,  0.5f,  0.5f, 0,1), p(-0.5f, -0.5f,  0.5f, 0,0), p( 0.5f, -0.5f,  0.5f, 1,0) });
    cube.triangles.push_back({ p(-0.5f,  0.5f,  0.5f, 0,1), p( 0.5f, -0.5f,  0.5f, 1,0), p( 0.5f,  0.5f,  0.5f, 1,1) });
    // Rear (z = -0.5)
    cube.triangles.push_back({ p( 0.5f,  0.5f, -0.5f, 0,1), p( 0.5f, -0.5f, -0.5f, 0,0), p(-0.5f, -0.5f, -0.5f, 1,0) });
    cube.triangles.push_back({ p( 0.5f,  0.5f, -0.5f, 0,1), p(-0.5f, -0.5f, -0.5f, 1,0), p(-0.5f,  0.5f, -0.5f, 1,1) });
    // Left (x = -0.5)
    cube.triangles.push_back({ p(-0.5f,  0.5f, -0.5f, 0,1), p(-0.5f, -0.5f, -0.5f, 0,0), p(-0.5f, -0.5f,  0.5f, 1,0) });
    cube.triangles.push_back({ p(-0.5f,  0.5f, -0.5f, 0,1), p(-0.5f, -0.5f,  0.5f, 1,0), p(-0.5f,  0.5f,  0.5f, 1,1) });
    // Right (x = +0.5)
    cube.triangles.push_back({ p( 0.5f,  0.5f,  0.5f, 0,1), p( 0.5f, -0.5f,  0.5f, 0,0), p( 0.5f, -0.5f, -0.5f, 1,0) });
    cube.triangles.push_back({ p( 0.5f,  0.5f,  0.5f, 0,1), p( 0.5f, -0.5f, -0.5f, 1,0), p( 0.5f,  0.5f, -0.5f, 1,1) });
    // Top (y = +0.5)
    cube.triangles.push_back({ p(-0.5f,  0.5f, -0.5f, 0,1), p(-0.5f,  0.5f,  0.5f, 0,0), p( 0.5f,  0.5f,  0.5f, 1,0) });
    cube.triangles.push_back({ p(-0.5f,  0.5f, -0.5f, 0,1), p( 0.5f,  0.5f,  0.5f, 1,0), p( 0.5f,  0.5f, -0.5f, 1,1) });
    // Bottom (y = -0.5)
    cube.triangles.push_back({ p(-0.5f, -0.5f,  0.5f, 0,1), p(-0.5f, -0.5f, -0.5f, 0,0), p( 0.5f, -0.5f, -0.5f, 1,0) });
    cube.triangles.push_back({ p(-0.5f, -0.5f,  0.5f, 0,1), p( 0.5f, -0.5f, -0.5f, 1,0), p( 0.5f, -0.5f,  0.5f, 1,1) });

    render.verticesMan.add(cube);

    
    // Game Loop
    while (!glfwWindowShouldClose(window)) {
        render.update();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}