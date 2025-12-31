#pragma once

#include <glm/glm.hpp>

class Transform {
private:

public:
	Transform();
	Transform(glm::vec3 pos);
	Transform(glm::vec3 pos, glm::vec3 rotAxis, float rotAngle);
	Transform(glm::vec3 pos, glm::vec3 rotAxis, float rotAngle, glm::vec3 size);
	~Transform();

	glm::mat4 matrix;
	
	glm::vec3 position;
	glm::vec3 rotationAxis;
	float rotationAngle;
	glm::vec3 scale;

	void recalculateMatrix();
};