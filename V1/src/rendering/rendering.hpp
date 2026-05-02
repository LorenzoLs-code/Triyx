#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <map>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class rendering {
private:
    bool verticesChanged;

    unsigned int VBO, VAO, EBO;
    unsigned int VBO_size_old, EBO_size_old;
    unsigned int shaderProgram;
    unsigned int mainTexture;

    std::string loadShader(const char* path);

    void applyCamera();

public:
    int windowWidth  = 800;
    int windowHeight = 600;

    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    float fov;

    float cameraYaw   = -90.0f;
    float cameraPitch = 0.0f;

    void moveCamera(float x, float y, float z);
    void teleportCamera(float x, float y, float z);

    void rotateCamera(float yawOffset, float pitchOffset);
    
    struct verticesPoint {
        float x;
        float y;
        float z;
        
        float u;
        float v;
    };

    struct triangle {
        verticesPoint a;
        verticesPoint b;
        verticesPoint c;
    };
    
    struct object{
        std::vector<triangle> triangles;

        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f); // X, Y, Z
        glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 scale    = glm::vec3(1.0f, 1.0f, 1.0f);

        unsigned int indexOffset = 0;
        unsigned int indexCount;
    };
    
    std::vector<object> objects;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    
    rendering();

    int update();

    class verticesManager {
    private:
        rendering& parent;
    public:
        verticesManager(rendering& p) : parent(p) {}
        int add(object object);
        void remove(int index);
        void clear();
        void objects_to_Data();
    };
    verticesManager verticesMan{*this};
};