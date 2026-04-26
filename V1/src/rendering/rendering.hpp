#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>

class rendering {
private:
    bool verticesChanged;

    unsigned int VBO, VAO;
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
    
    rendering();
    int update();

    class verticesManager {
    private:
        rendering& parent;
    public:
        verticesManager(rendering& p) : parent(p) {}
        object& get_object(int);
        int add(object);
        void remove(int);
        void clear();
        void objects_to_vertices();
    };
    
    verticesManager verticesMan{*this};
};