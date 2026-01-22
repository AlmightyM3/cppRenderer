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

}

void Texture::setParameter(GLenum parameter, GLint value) {
	glTextureParameteri(Texture::textureUnit, parameter, value);
}

void Texture::bind(int shaderTexUnit) {
	glBindTextureUnit(shaderTexUnit, Texture::textureUnit);
}