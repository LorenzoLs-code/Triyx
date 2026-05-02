#include <GL/glew.h> // for rendendering whats in the window
#include <GLFW/glfw3.h> // for makeing a window
#include "external/stb_image.h" // for reading textures 

#include "rendering/rendering.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    glfwInit(); // initialize GLFW
    int startWindowWidth = 800;
    int startWindowHeight = 600;
    GLFWwindow* window = glfwCreateWindow(startWindowWidth, startWindowHeight, "Triyx", NULL, NULL); // Create a window
    glfwMakeContextCurrent(window); // show the window
    rendering render;
    render.windowHeight = startWindowWidth; render.windowHeight = startWindowHeight;

    glfwSetWindowUserPointer(window, &render);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        rendering* render = (rendering*)glfwGetWindowUserPointer(window);
        render->windowWidth  = width;
        render->windowHeight = height;
    });

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

    rendering::object cubeB;

    // 8 corners of the cube, each side as 2 triangles
    // Front (z = +0.5)
    cubeB.triangles.push_back({ p(-0.5f,  0.5f,  0.5f, 0,1), p(-0.5f, -0.5f,  0.5f, 0,0), p( 0.5f, -0.5f,  0.5f, 1,0) });
    cubeB.triangles.push_back({ p(-0.5f,  0.5f,  0.5f, 0,1), p( 0.5f, -0.5f,  0.5f, 1,0), p( 0.5f,  0.5f,  0.5f, 1,1) });
    // Rear (z = -0.5)
    cubeB.triangles.push_back({ p( 0.5f,  0.5f, -0.5f, 0,1), p( 0.5f, -0.5f, -0.5f, 0,0), p(-0.5f, -0.5f, -0.5f, 1,0) });
    cubeB.triangles.push_back({ p( 0.5f,  0.5f, -0.5f, 0,1), p(-0.5f, -0.5f, -0.5f, 1,0), p(-0.5f,  0.5f, -0.5f, 1,1) });
    // Left (x = -0.5)
    cubeB.triangles.push_back({ p(-0.5f,  0.5f, -0.5f, 0,1), p(-0.5f, -0.5f, -0.5f, 0,0), p(-0.5f, -0.5f,  0.5f, 1,0) });
    cubeB.triangles.push_back({ p(-0.5f,  0.5f, -0.5f, 0,1), p(-0.5f, -0.5f,  0.5f, 1,0), p(-0.5f,  0.5f,  0.5f, 1,1) });
    // Right (x = +0.5)
    cubeB.triangles.push_back({ p( 0.5f,  0.5f,  0.5f, 0,1), p( 0.5f, -0.5f,  0.5f, 0,0), p( 0.5f, -0.5f, -0.5f, 1,0) });
    cubeB.triangles.push_back({ p( 0.5f,  0.5f,  0.5f, 0,1), p( 0.5f, -0.5f, -0.5f, 1,0), p( 0.5f,  0.5f, -0.5f, 1,1) });
    // Top (y = +0.5)
    cubeB.triangles.push_back({ p(-0.5f,  0.5f, -0.5f, 0,1), p(-0.5f,  0.5f,  0.5f, 0,0), p( 0.5f,  0.5f,  0.5f, 1,0) });
    cubeB.triangles.push_back({ p(-0.5f,  0.5f, -0.5f, 0,1), p( 0.5f,  0.5f,  0.5f, 1,0), p( 0.5f,  0.5f, -0.5f, 1,1) });
    // Bottom (y = -0.5)
    cubeB.triangles.push_back({ p(-0.5f, -0.5f,  0.5f, 0,1), p(-0.5f, -0.5f, -0.5f, 0,0), p( 0.5f, -0.5f, -0.5f, 1,0) });
    cubeB.triangles.push_back({ p(-0.5f, -0.5f,  0.5f, 0,1), p( 0.5f, -0.5f, -0.5f, 1,0), p( 0.5f, -0.5f,  0.5f, 1,1) });


    cubeB.position = glm::vec3(2.0f, 0.0f, 0.0f); // zweiter Würfel 2 Einheiten rechts
    cubeB.rotation = glm::vec3(0.0f, 45.0f, 0.0f); // 45 Grad gedreht
    render.verticesMan.add(cubeB);

    
    // Game Loop
    while (!glfwWindowShouldClose(window)) {
        render.update();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}