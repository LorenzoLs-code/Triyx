#include <GL/glew.h> // for rendendering whats in the window
#include <GLFW/glfw3.h> // for makeing a window
#include "external/stb_image.h" // for reading textures 

#include "rendering/rendering.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    glfwInit(); // initialize GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "LittleStar", NULL, NULL); // Create a window
    glfwMakeContextCurrent(window); // show the window
    rendering render;

    // Game Loop
    while (!glfwWindowShouldClose(window)) {
        render.update();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}