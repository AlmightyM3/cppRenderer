#pragma once

#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>

struct vertex { 
    glm::vec3 pos, normal; glm::vec2 texCoord; 

    vertex(glm::vec3 p, glm::vec3 n, glm::vec2 t) : pos(p), normal(n), texCoord(t) {}
};

class Mesh {
private:
    std::vector<vertex> vertices;
    std::vector<uint32_t> indices;

    GLuint VAO;

    void uploadData();

public:
    Mesh(std::vector<vertex> initialVertices, std::vector<uint32_t> initialIndices);

    ~Mesh();

    void render();
};