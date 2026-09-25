#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "texture.h"

Texture::Texture(std::string filePath) {
	int width, height, nrChannels;
	unsigned char *data = stbi_load(filePath.data(), &width, &height, &nrChannels, 0);

	GLuint texUnit;
	glCreateTextures(GL_TEXTURE_2D, 1, &texUnit);

	glTextureParameteri(texUnit, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(texUnit, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(texUnit, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(texUnit, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureStorage2D(texUnit, 1, GL_RGBA8, width, height);
	glTextureSubImage2D(texUnit, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	Texture::textureUnit = texUnit;

	stbi_image_free(data);
}

Texture::Texture(GLint type, GLenum fomat, GLsizei width, GLsizei height, const void* color) {
	GLuint texUnit;
	glCreateTextures(GL_TEXTURE_2D, 1, &texUnit);

	glTextureParameteri(texUnit, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(texUnit, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(texUnit, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(texUnit, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTextureStorage2D(texUnit, 1, type, width, height);
	glClearTexImage(texUnit, 0, GL_RGBA, fomat, color);

	Texture::textureUnit = texUnit;
}

Texture::~Texture() {
	glDeleteTextures(1, &(Texture::textureUnit));
}

void Texture::setParameter(GLenum parameter, GLint value) {
	glTextureParameteri(Texture::textureUnit, parameter, value);
}

void Texture::bind(int shaderTexUnit) {
	glBindTextureUnit(shaderTexUnit, Texture::textureUnit);
}

void Texture::resize(GLsizei width, GLsizei height) {
	GLint format;
	glGetTextureLevelParameteriv(Texture::textureUnit, 0, GL_TEXTURE_INTERNAL_FORMAT, &format);
	GLint wrap_s, wrap_t, min, mag;
	glGetTextureParameteriv(Texture::textureUnit, GL_TEXTURE_WRAP_S, &wrap_s);
	glGetTextureParameteriv(Texture::textureUnit, GL_TEXTURE_WRAP_T, &wrap_t);
	glGetTextureParameteriv(Texture::textureUnit, GL_TEXTURE_MIN_FILTER, &min);
	glGetTextureParameteriv(Texture::textureUnit, GL_TEXTURE_MAG_FILTER, &mag);

	glDeleteTextures(1, &(Texture::textureUnit));

	GLuint texUnit;
	glCreateTextures(GL_TEXTURE_2D, 1, &texUnit);

	glTextureParameteri(texUnit, GL_TEXTURE_WRAP_S, wrap_s);
	glTextureParameteri(texUnit, GL_TEXTURE_WRAP_T, wrap_t);
	glTextureParameteri(texUnit, GL_TEXTURE_MIN_FILTER, min);
	glTextureParameteri(texUnit, GL_TEXTURE_MAG_FILTER, mag);

	glTextureStorage2D(texUnit, 1, format, width, height);

	Texture::textureUnit = texUnit;
}

GLuint Texture::getTextureUnit() {
	return Texture::textureUnit;
}