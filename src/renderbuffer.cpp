#include "renderbuffer.h"

Renderbuffer::Renderbuffer(GLenum component, int width, int height) {
	GLuint rbo;
	glCreateRenderbuffers(1, &rbo);
	glNamedRenderbufferStorage(rbo, component, width, height);
	Renderbuffer::renderbuffer = rbo;
}

Renderbuffer::~Renderbuffer() {
	glDeleteRenderbuffers(1, &(Renderbuffer::renderbuffer));
}

GLuint Renderbuffer::getRenderbuffer() {
	return Renderbuffer::renderbuffer;
}

void Renderbuffer::resize(int width, int height) {
	GLint format;
	glGetNamedRenderbufferParameteriv(Renderbuffer::renderbuffer, GL_RENDERBUFFER_INTERNAL_FORMAT, &format);
	glNamedRenderbufferStorage(Renderbuffer::renderbuffer, format, width, height);
}

void Renderbuffer::bind() {
	glBindRenderbuffer(GL_RENDERBUFFER, Renderbuffer::renderbuffer);
}
void Renderbuffer::unbind() {
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}