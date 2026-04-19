#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

std::string loadFile(const char* path) {
    std::ifstream file(path); // open file
    if(!file.is_open()) { // check if the file was opened
        std::cout << "Failed to open file: " << path << std::endl;
        return "";
    }
    std::stringstream buffer; // make a storage for the data
    buffer << file.rdbuf(); // put the data in the buffer
    file.close(); // close file
    return buffer.str(); // make the buffer into a string and return it
}

int main() {
    glfwInit(); // initialize GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "LittleStar", NULL, NULL); // Create a window
    glfwMakeContextCurrent(window); // show the window
    glewInit(); // initialize glew

    // == Make a shader programm ==
    //load vertexShaderSource
    std::string vertexShaderCode = loadFile("../shaders/vertex.glsl");
    const char* vertexShaderSource = vertexShaderCode.c_str();

    //load fragmentShaderSource
    std::string fragmentShaderCode = loadFile("../shaders/fragment.glsl");
    const char* fragmentShaderSource = fragmentShaderCode.c_str();

    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // create vertex shader variable
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // read the shader code and assign it to the shader/variable
    glCompileShader(vertexShader); // compile the shader

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // create fragment shader variable
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // read the shader code and assign it to the shader/variable
    glCompileShader(fragmentShader); // compile the shader

    // shader programm
    unsigned int shaderProgram = glCreateProgram(); // create a programm to run the shaders
    glAttachShader(shaderProgram, vertexShader); // assign the vertex shader to the programm
    glAttachShader(shaderProgram, fragmentShader); // assign the fragment shader to the programm
    glLinkProgram(shaderProgram); // make it usable
    // ==  ==  ==

    // Vertices cords (the corners for the triangle)
    float vertices[] = {
         0.0f,  0.5f, 0.0f, // (first corner)
        -0.5f, -0.5f, 0.0f, // (second corner)
         0.5f, -0.5f, 0.0f // (third corner)
    };

    unsigned int VBO, VAO; // create ids(pointers) to send the vertice(VBO) and what to do with the vertices (what vertices is connected to what vertice)(VAO) to the GPU
    glGenVertexArrays(1, &VAO); // define VAO as "blue print" for the triangle
    glGenBuffers(1, &VBO); // define VBO as a storage in the gpu
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // say the storage is for vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // send data to the gpu
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // say the gpu the data it received
    glEnableVertexAttribArray(0); // activate Buffer slot 0

    // Game Loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}