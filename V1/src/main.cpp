#include <GL/glew.h> // for rendendering whats in the window
#include <GLFW/glfw3.h> // for makeing a window
#include "external/stb_image.h" // for reading textures 

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

    // == load texture ==

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int width, height, channels;
    unsigned char* textureData = stbi_load("../assets/textures/test2.png", &width, &height, &channels, 0);

    if (!textureData) {
        std::cout << "Failed to load texture: " << std::endl;
        texture = 'a';
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(textureData);


    // Vertices cords (the corners for the triangle)
    float vertices[] = {
    // X      Y      Z     U     V
     0.0f,  0.5f, 0.0f, 0.5f, 1.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f
    };

    unsigned int VBO, VAO; // create ids(pointers) to send the vertice(VBO) and what to do with the vertices (what vertices is connected to what vertice)(VAO) to the GPU
    glGenVertexArrays(1, &VAO); // define VAO as "blue print" for the triangle
    glGenBuffers(1, &VBO); // define VBO as a storage in the gpu
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // say the storage is for vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW); // send data to the gpu
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // say the gpu how to interpret data it received, in this case slot 0 = vertices 0-2(X,Y,Z)
    glEnableVertexAttribArray(0); // activate Buffer slot 0

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // say the gpu how to interpret data it received, in this case slot 1 = texture 3-4(U,V)
    glEnableVertexAttribArray(1); // activate Buffer slot 1

    // Game Loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}