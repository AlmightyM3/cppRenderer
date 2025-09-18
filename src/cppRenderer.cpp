#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "shader.h"

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

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};  

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

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Shader shader("test.vert","test.frag");

	// Start main loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(VAO);
		shader.use();
		shader.setFloat("time", (float)glfwGetTime());
		glDrawArrays(GL_TRIANGLES, 0, 3);

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
