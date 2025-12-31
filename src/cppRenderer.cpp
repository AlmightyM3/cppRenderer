#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"
#include "transform.h"


static void OpenGL_ErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
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
			default: return "SOURCE " + source;
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
			default: return "TYPE " + type;
		}
	}();

	auto const severity_str = [severity]() {
		switch (severity) {
			case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
			case GL_DEBUG_SEVERITY_LOW: return "LOW";
			case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
			case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
			default: return "SEVERITY " + severity;
		}
	}();
	std::cerr << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
}

static void GLFW_ErrorCallback(int error, const char* description)
{
	std::cerr << "GLFW ERROR: " << description << "\n";
}

std::unordered_map<int, bool> keys;
static void GLFW_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		keys[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		keys[key] = false;
	}
}

FreeCamera cam;
static void GLFW_ResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	cam.aspectRatio = ((float)width) / ((float)height);
	cam.recalculateMatrix();
}

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
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	// Set up OpenGL
	glfwMakeContextCurrent(window);
	int version = gladLoadGL(glfwGetProcAddress);
	std::cout << "GL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << "\n";

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(OpenGL_ErrorCallback, nullptr);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	Mesh suzanne = Mesh("Suzanne.obj");
	Transform suzanneTransform = Transform(glm::vec3(2.0f, 0.0f, 1.0f));
	Mesh cube = Mesh("Cube.obj");
	Transform cubeTransform = Transform();

	Texture uvGrid = Texture("uvGrid.png");

	Shader shader("test.vert","test.frag");
	
	cam = FreeCamera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 16.0f/9.0f, 45.0f);

	double mouseX, mouseY = -1.0f;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	double oldTime = glfwGetTime();

	// Start main loop
	while (!glfwWindowShouldClose(window))
	{
		// Handle events
		glfwPollEvents();

		double newTime = glfwGetTime();
		float dt = (float)(newTime - oldTime);
		oldTime = newTime;
		
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		if (!(io.WantCaptureMouse || io.WantCaptureKeyboard) && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			cam.update(keys, (float)(xpos - mouseX), (float)(ypos - mouseY), dt);
		} else
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			
		mouseX = xpos;
		mouseY = ypos;

		cubeTransform.rotationAngle += dt * 0.5f;
		cubeTransform.recalculateMatrix();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		uvGrid.bind(0);
		shader.setInt("testImg", 0);
		shader.setMat4("camera", cam.matrix);

		shader.setMat4("transform", suzanneTransform.matrix );
		suzanne.render();

		shader.setMat4("transform", cubeTransform.matrix);
		cube.render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update screen
		glfwSwapBuffers(window);
	} 

	// Close the app
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
