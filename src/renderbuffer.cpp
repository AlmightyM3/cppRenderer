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

void Renderbuffer::bind() {
	glBindRenderbuffer(GL_RENDERBUFFER, Renderbuffer::renderbuffer);
}
void Renderbuffer::unbind() {
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}