#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

Camera::Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up) {
	Camera::position = pos;
	Camera::direction = dir;
	Camera::worldUp = up;

	Camera::aspectRatio = 1.0f;
	Camera::fov = glm::radians(45.0f);

	Camera::recalculateMatrix();
}
Camera::Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, float ratio, float fov) {
	Camera::position = pos;
	Camera::direction = dir;
	Camera::worldUp = up;

	Camera::aspectRatio = ratio;
	Camera::fov = glm::radians(fov);

	Camera::recalculateMatrix();
}

Camera::~Camera() {

}

void Camera::recalculateMatrix() {
	Camera::matrix = glm::perspective(Camera::fov, Camera::aspectRatio, 0.01f, 100.0f) * glm::lookAt(Camera::position, Camera::position + Camera::direction, Camera::worldUp);
}

void Camera::update(std::unordered_map<int, bool> keys, float mouseDx, float mouseDy, float dt) {
	Camera::recalculateMatrix();
}


void FreeCamera::update(std::unordered_map<int, bool> keys, float mouseDx, float mouseDy, float dt) {
	FreeCamera::pitch -= mouseDy * FreeCamera::mouseSensitivity;
	FreeCamera::yaw += mouseDx * FreeCamera::mouseSensitivity;

	if (FreeCamera::pitch > 89.0f)
		FreeCamera::pitch = 89.0f;
	if (FreeCamera::pitch < -89.0f)
		FreeCamera::pitch = -89.0f; 

	glm::vec3 newDirection;
	newDirection.x = cos(glm::radians(FreeCamera::yaw)) * cos(glm::radians(FreeCamera::pitch));
	newDirection.y = sin(glm::radians(FreeCamera::pitch));
	newDirection.z = sin(glm::radians(FreeCamera::yaw)) * cos(glm::radians(FreeCamera::pitch));
	FreeCamera::direction = glm::normalize(newDirection);

	
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
		FreeCamera::position += FreeCamera::moveSpeed * FreeCamera::direction;
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
		FreeCamera::position -= FreeCamera::moveSpeed * FreeCamera::direction;
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
		FreeCamera::position -= glm::normalize(glm::cross(FreeCamera::direction, FreeCamera::worldUp)) * FreeCamera::moveSpeed;
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
		FreeCamera::position += glm::normalize(glm::cross(FreeCamera::direction, FreeCamera::worldUp)) * FreeCamera::moveSpeed;
	if (keys[GLFW_KEY_Q])
		FreeCamera::position += FreeCamera::moveSpeed * FreeCamera::worldUp;
	if (keys[GLFW_KEY_E])
		FreeCamera::position -= FreeCamera::moveSpeed * FreeCamera::worldUp;

	FreeCamera::recalculateMatrix();
}