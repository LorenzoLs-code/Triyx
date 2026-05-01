#include "rendering.hpp"
#include "../external/stb_image.h" // for reading textures 

#include <map>
#include <iostream>
#include <fstream>
#include <sstream>


std::string rendering::loadShader(const char* path) {
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

rendering::rendering() {
    glewInit(); // initialize glew

    // Vertices cords for the start triangels (the corners for the triangle)
    float startVertices[] = {
    // X      Y      Z     U     V
     0.0f,  0.5f, 0.0f, 0.5f, 1.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f
    };
    unsigned int startIndices[] = {
     0, 1, 2,  0, 2, 3,
     4, 5, 6,  4, 6, 7,  
     0, 4, 7,  0, 7, 3, 
     1, 5, 6,  1, 6, 2, 
     3, 7, 6,  3, 6, 2, 
     0, 4, 5,  0, 5, 1 
    };

    verticesChanged = false;
 
    /* ==============
        load Texture
       ============== */
    glGenTextures(1, &mainTexture);
    glBindTexture(GL_TEXTURE_2D, mainTexture);


    int width, height, channels;
    unsigned char* data = stbi_load("../assets/textures/test2.png", &width, &height, &channels, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    /* ======================================
        Preparation for Vertices and Indices
       ====================================== */
    // -- Vertices --
    glGenVertexArrays(1, &VAO); // define VAO as "blue print" for the triangle
    glGenBuffers(1, &VBO); // define VBO as a storage in the gpu
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // say the storage is for vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(startVertices), startVertices, GL_DYNAMIC_DRAW); // send data to the gpu

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // say the gpu how to interpret data it received, in this case slot 0 = vertices 0-2(X,Y,Z)
    glEnableVertexAttribArray(0); // activate Buffer slot 0

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // say the gpu how to interpret data it received, in this case slot 1 = texture 3-4(U,V)
    glEnableVertexAttribArray(1); // activate Buffer slot 1
    
    // -- Indices --
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(startIndices), startIndices, GL_DYNAMIC_DRAW);

        
    /* =========================
        Preparation for Shaders
       ========================= */
    // vertexShader
    std::string vertexShaderCode = loadShader("../shaders/vertex.glsl"); // load the shader code
    const char* vertexShaderSource = vertexShaderCode.c_str(); // string --> char*
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // create vertex shader variable
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // read the shader code and assign it to the shader/variable
    glCompileShader(vertexShader); // compile the shader

    // fragmentShader
    std::string fragmentShaderCode = loadShader("../shaders/fragment.glsl"); // load the shader code
    const char* fragmentShaderSource = fragmentShaderCode.c_str(); // string --> char*
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // create fragment shader variable
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // read the shader code and assign it to the shader/variable
    glCompileShader(fragmentShader); // compile the shader


    // shader programm
    shaderProgram = glCreateProgram(); // create a programm to run the shaders
    glAttachShader(shaderProgram, vertexShader); // assign the vertex shader to the programm
    glAttachShader(shaderProgram, fragmentShader); // assign the fragment shader to the programm
    glLinkProgram(shaderProgram); // make it usable
}

int rendering::update() {
    if(verticesChanged) {
        verticesMan.objects_to_Data();

        unsigned V_size = vertices.size();
        if(VBO_size_old < V_size) {
            glBindBuffer(GL_ARRAY_BUFFER, VBO); // say the storage is for vertices
            glBufferData(GL_ARRAY_BUFFER, V_size * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW); // send data to the gpu
            VBO_size_old = V_size;
        } else {glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());}

        unsigned I_size = indices.size();
        if(EBO_size_old < I_size) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, I_size * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);
            EBO_size_old = I_size;
        } else {glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned int), indices.data());}
        
        verticesChanged = false;
    };
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, mainTexture);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    return 0;
}

// verticesManager functions
int rendering::verticesManager::add(rendering::object object) {
    parent.objects.push_back(object); // add object to vertices(vector) 
    parent.verticesChanged = true; // say the vertices has changed
    return parent.objects.size() - 1; // return the index of the object
};

void rendering::verticesManager::remove(int index) {
    parent.objects.erase(parent.objects.begin() + index); // delete object by index
    parent.verticesChanged = true; // say the vertices has changed
};

void rendering::verticesManager::clear() {
    parent.objects.clear(); // delete whats in the vectorw
    parent.verticesChanged = true; // say the vertices has changed
};

void rendering::verticesManager::objects_to_Data() { // a big loop to converts objects to Data
    parent.vertices.clear();
    parent.indices.clear();
    
    unsigned int vertices_index_counter = 0; 
    std::map<std::tuple<float, float, float>, unsigned int> pointIndex;
    float x,y,z;

    for(const auto& obj : parent.objects) {
        pointIndex.clear();
        for(const auto& tri : obj.triangles) {
            // point A
            x = tri.a.x;
            y = tri.a.y;
            z = tri.a.z;
            if(pointIndex.find({x, y, z}) == pointIndex.end()) {
                parent.vertices.push_back(x);
                parent.vertices.push_back(y);
                parent.vertices.push_back(z);
                parent.vertices.push_back(tri.a.u);
                parent.vertices.push_back(tri.a.v);
                
                pointIndex[{x, y, z}] = vertices_index_counter;
                vertices_index_counter += 1;
            }

            parent.indices.push_back(pointIndex[{x, y, z}]);

            // point B
            x = tri.b.x;
            y = tri.b.y;
            z = tri.b.z;
            if(pointIndex.find({x, y, z}) == pointIndex.end()) {
                parent.vertices.push_back(x);
                parent.vertices.push_back(y);
                parent.vertices.push_back(z);
                parent.vertices.push_back(tri.b.u);
                parent.vertices.push_back(tri.b.v);
                
                pointIndex[{x, y, z}] = vertices_index_counter;
                vertices_index_counter += 1;
            }

            parent.indices.push_back(pointIndex[{x, y, z}]);
    
            // point C
            x = tri.c.x;
            y = tri.c.y;
            z = tri.c.z;
            if(pointIndex.find({x, y, z}) == pointIndex.end()) {
                parent.vertices.push_back(x);
                parent.vertices.push_back(y);
                parent.vertices.push_back(z);
                parent.vertices.push_back(tri.c.u);
                parent.vertices.push_back(tri.c.v);
                
                pointIndex[{x, y, z}] = vertices_index_counter;
                vertices_index_counter += 1;
            }

            parent.indices.push_back(pointIndex[{x, y, z}]);
        };
    };
};