#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

void GLFW_ErrorCallback(int error, const char* description)
{
	std::cout << "GLFW ERROR: " << description << "\n";
}

static void GLFW_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
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
		std::cout << "GLFW ERROR: GLFW initialization failed.\n"; // Initialization failed
		return -1;
	}

	// Set error calback for glfw
	glfwSetErrorCallback(GLFW_ErrorCallback);

	// Create the window
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "cppRenderer", NULL, NULL);
	if (!window)
	{
		std::cout << "GLFW ERROR: Window or OpenGL context creation failed.\n";// Window or OpenGL context creation failed
		glfwTerminate();
		return -1;
	}
	// Set callback for user inputs
	glfwSetKeyCallback(window, GLFW_KeyCallback);

	// Set up OpenGL
	glfwMakeContextCurrent(window);
	int version = gladLoadGL(glfwGetProcAddress);
	std::cout << "GL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << "\n";

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Start main loop
	while (!glfwWindowShouldClose(window))
	{
		glBindVertexArray(VAO);
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
