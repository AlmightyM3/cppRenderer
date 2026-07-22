#include "framebuffer.h"

Framebuffer::Framebuffer() {
	GLuint fbo;
	glCreateFramebuffers(1, &fbo);
	Framebuffer::framebuffer = fbo;
}

Framebuffer::~Framebuffer() {
	glDeleteFramebuffers(1, &(Framebuffer::framebuffer));
}

void Framebuffer::setTexture(GLenum attatchment, GLuint texture) {
	glNamedFramebufferTexture(Framebuffer::framebuffer, attatchment, texture, 0);
}

void Framebuffer::drawBuffers(GLsizei count, const GLenum* attachments) {
	glNamedFramebufferDrawBuffers(Framebuffer::framebuffer, count, attachments);
}

void Framebuffer::clear(GLenum buffer, GLint drawbuffer, const GLfloat* value) {
	glClearNamedFramebufferfv(Framebuffer::framebuffer, buffer, drawbuffer, value);
}