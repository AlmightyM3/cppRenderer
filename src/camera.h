#pragma once

#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>

class Camera {
private:

public:
	Camera() {}
	Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up);
	Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, float ratio, float fov);

	~Camera();
	
	void recalculateMatrix();

	float aspectRatio;
	float fov;

	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 worldUp;

	glm::mat4 matrix;
};