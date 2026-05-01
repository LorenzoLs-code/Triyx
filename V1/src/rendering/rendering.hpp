#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <map>
#include <string>


class rendering {
private:
    bool verticesChanged;

    unsigned int VBO, VAO, EBO;
    unsigned int VBO_size_old, EBO_size_old;
    unsigned int shaderProgram;
    unsigned int mainTexture;

    std::string loadShader(const char* path);

public:
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