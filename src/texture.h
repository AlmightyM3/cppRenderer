#include <string>
#include <glad/gl.h>

class Texture {
private:
	GLuint textureUnit;
public:
	Texture(std::string filePath);

	~Texture();

	void setParameter(GLenum parameter, GLint value);
	void bind(int shaderTexUnit);
};