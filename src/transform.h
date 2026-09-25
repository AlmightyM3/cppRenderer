#pragma once

#include <glm/glm.hpp>

class Transform {
private:

public:
	Transform(glm::vec3 pos = {}, glm::vec3 rotAxis = { 1.0f, 0.0f, 0.0f }, float rotAngle = 0.0f, glm::vec3 size = { 1.0f, 1.0f, 1.0f });
	~Transform();

	glm::mat4 matrix;
	
	glm::vec3 position;
	glm::vec3 rotationAxis;
	float rotationAngle;
	glm::vec3 scale;

	void recalculateMatrix();
};