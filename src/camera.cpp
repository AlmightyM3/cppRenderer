#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

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