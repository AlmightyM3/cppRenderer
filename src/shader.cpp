#include "shader.h"
#include <fstream>
#include <iostream>

void handleCompileError(GLuint shader)
{
	GLint result = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		char buffer[1024];
		glGetShaderInfoLog(shader, 1024, NULL, buffer);
		if (buffer[0])
			std::cerr << "ERROR Shader compile error: " << buffer << "\n";
		exit(-1);
	};
}
void handleLinkError(GLuint program)
{
	GLint result = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result == GL_FALSE) {
		char buffer[1024];
		glGetProgramInfoLog(program, 1024, NULL, buffer);
		if (buffer[0])
			std::cerr << "ERROR Shader link error: " << buffer << "\n";
		exit(-1);
	};
}

Shader::Shader(std::string vertexPath, std::string fragmentPath) {
	Shader::program = glCreateProgram();

	Shader::compileShader(vertexPath, GL_VERTEX_SHADER);
	Shader::compileShader(fragmentPath, GL_FRAGMENT_SHADER);

	Shader::calculateUniforms();
}

Shader::Shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath) {
	Shader::program = glCreateProgram();

	Shader::compileShader(vertexPath, GL_VERTEX_SHADER);
	Shader::compileShader(fragmentPath, GL_FRAGMENT_SHADER);
	Shader::compileShader(geometryPath, GL_GEOMETRY_SHADER);

	Shader::calculateUniforms();
}

Shader::~Shader() {
	glDeleteProgram(Shader::program);
}

void Shader::compileShader(std::string shaderPath, GLenum shaderType) {
	std::ifstream shaderFile(shaderPath);
	if (!shaderFile.is_open()){
		std::cerr << "Failed to open file: " << shaderPath << "\n";
		exit(-1);
	}

	std::string shaderSource{ std::istreambuf_iterator<char>(shaderFile), std::istreambuf_iterator<char>() };
	shaderFile.close();

	const char* shaderSourceC = shaderSource.c_str();

	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSourceC, NULL);
	glCompileShader(shader);
	handleCompileError(shader);
	glAttachShader(Shader::program, shader);
	glDeleteShader(shader);
	glLinkProgram(Shader::program);
	handleLinkError(Shader::program);
}

void Shader::use() {
	glUseProgram(Shader::program);
}

void Shader::calculateUniforms() {
	Shader::uniforms.clear();
	
	GLint uniformCount = 0;
	glGetProgramiv(Shader::program, GL_ACTIVE_UNIFORMS, &uniformCount);

	if (uniformCount > 0) {
		GLint maxNameLen = 0;
		glGetProgramiv(Shader::program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLen);
		auto uniformName = std::make_unique<char[]>(maxNameLen);

		GLsizei length = 0;
		GLsizei count = 0;
		GLenum type = GL_NONE;

		for (GLint i = 0; i < uniformCount; ++i)
		{
			glGetActiveUniform(Shader::program, i, maxNameLen, &length, &count, &type, uniformName.get());

			uniformInfo tempUniformInfo = {};
			tempUniformInfo.location = glGetUniformLocation(Shader::program, uniformName.get());
			tempUniformInfo.count = count;

			Shader::uniforms.emplace(std::make_pair(std::string(uniformName.get(), length), tempUniformInfo));
		}
	}
}

void Shader::setInt(std::string name, int value) {
	glProgramUniform1i(Shader::program, Shader::uniforms[name].location, value);
}

void Shader::setFloat(std::string name, float value) {
	glProgramUniform1f(Shader::program, Shader::uniforms[name].location, value);
}
// to set a array glProgramUniformXXv(program_name, uniforms["my_array[0]"].location, uniforms["my_array[0]"].count, my_array);