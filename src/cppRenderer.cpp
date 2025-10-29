#include <iostream>
#include <vector>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "mesh.h"


void OpenGL_ErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
{
	auto const src_str = [source]() {
		switch (source)
		{
			case GL_DEBUG_SOURCE_API: return "API";
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
			case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
			case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
			case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
			case GL_DEBUG_SOURCE_OTHER: return "OTHER";
		}
	}();

	auto const type_str = [type]() {
		switch (type)
		{
			case GL_DEBUG_TYPE_ERROR: return "ERROR";
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
			case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
			case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
			case GL_DEBUG_TYPE_MARKER: return "MARKER";
			case GL_DEBUG_TYPE_OTHER: return "OTHER";
		}
	}();

	auto const severity_str = [severity]() {
		switch (severity) {
			case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
			case GL_DEBUG_SEVERITY_LOW: return "LOW";
			case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
			case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
		}
	}();
	std::cerr << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
}

void GLFW_ErrorCallback(int error, const char* description)
{
	std::cerr << "GLFW ERROR: " << description << "\n";
}

static void GLFW_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void GLFW_ResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//std::vector <vertex> vertices = {
//	{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
//	{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
//	{glm::vec3(0.0f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
//};  
//
//std::vector<uint32_t> indices = {
//	0, 1, 2
//};

int main()
{
	// Start glfw
	if (!glfwInit())
	{
		std::cerr << "GLFW ERROR: GLFW initialization failed.\n"; // Initialization failed
		return -1;
	}

	// Set error calback for glfw
	glfwSetErrorCallback(GLFW_ErrorCallback);

	// Create the window
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "cppRenderer", NULL, NULL);
	if (!window)
	{
		std::cerr << "GLFW ERROR: Window or OpenGL context creation failed.\n";// Window or OpenGL context creation failed
		glfwTerminate();
		return -1;
	}
	// Set callback for user inputs
	glfwSetKeyCallback(window, GLFW_KeyCallback);
	glfwSetFramebufferSizeCallback(window, GLFW_ResizeCallback);


	// Set up OpenGL
	glfwMakeContextCurrent(window);
	int version = gladLoadGL(glfwGetProcAddress);
	std::cout << "GL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << "\n";

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(OpenGL_ErrorCallback, nullptr);


	Mesh triangle = Mesh(
		{
			{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
			{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
			{glm::vec3(0.0f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		}, 
		{
			0, 1, 2
		}
	);
	Mesh square = Mesh(
		{
			{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
			{glm::vec3(0.75f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
			{glm::vec3(0.5f, 0.75f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
			{glm::vec3(0.75f, 0.75f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		},
		{
			0, 1, 2,
			1, 3, 2
		}
	);

	Shader shader("test.vert","test.frag");

	// Start main loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		shader.setFloat("time", (float)glfwGetTime());
		triangle.render();
		square.render();

		// Update screen
		glfwSwapBuffers(window);

		// Handle events
		glfwPollEvents();
	}

	// Close the app
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
