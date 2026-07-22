#pragma once

#include <string>
#include <glad/gl.h>

class Texture {
private:
	GLuint textureUnit;
public:
	Texture(std::string filePath);
	Texture(GLint type, GLenum fomat, GLsizei width, GLsizei height, const void* color);

	~Texture();

	void setParameter(GLenum parameter, GLint value);
	void bind(int shaderTexUnit);
};