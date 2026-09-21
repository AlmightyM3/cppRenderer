#pragma once

#include <glad/gl.h>

class Renderbuffer {
private:
	GLuint renderbuffer;
public:
	Renderbuffer(GLenum component, int width, int height);

	~Renderbuffer();

	GLuint getRenderbuffer();

	void bind();
	void unbind();
};