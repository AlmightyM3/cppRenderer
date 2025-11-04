#pragma once

#include <string>
#include <glad/gl.h>
#include <unordered_map>
#include <glm/glm.hpp>

struct uniformInfo
{
    GLint location;
    GLsizei count;
};

class Shader {
private:
    GLuint program;
    std::unordered_map<std::string, uniformInfo> uniforms;

    void compileShader(std::string shaderPath, GLenum shaderType);
    void calculateUniforms();

public:
    Shader(std::string vertexPath, std::string fragmentPath);
    Shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath);

    ~Shader();

    void use();

    void setInt(std::string name, int value);
    void setFloat(std::string name, float value);
    void setMat4(std::string name, glm::mat4 value);
};