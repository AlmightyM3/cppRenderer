#pragma once

#include <glad/gl.h>

class Framebuffer {
private:
	GLuint framebuffer;
public:
	Framebuffer();

	~Framebuffer();

	void setTexture(GLenum attatchment, GLuint texture);

	void drawBuffers(GLsizei count, const GLenum* attachments);

	void clear(GLenum buffer, GLint drawbuffer, const GLfloat* value); // drawbuffer is for multiple color buffers
};