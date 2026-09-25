#include "transform.h"
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform(glm::vec3 pos, glm::vec3 rotAxis, float rotAngle, glm::vec3 size) {
	Transform::position = pos;
	Transform::rotationAxis = rotAxis;
	Transform::rotationAngle = rotAngle;
	Transform::scale = size;
	Transform::recalculateMatrix();
}

Transform::~Transform() {

}

void Transform::recalculateMatrix() {
	Transform::matrix = glm::translate(glm::rotate(glm::scale(glm::mat4(1.0f), Transform::scale), Transform::rotationAngle, Transform::rotationAxis), Transform::position);
}