#include "transform.h"
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform() {
	Transform::position = glm::vec3(0.0f);
	Transform::rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	Transform::rotationAngle = 0.0f;
	Transform::scale = glm::vec3(1.0f);
	Transform::recalculateMatrix();
}
Transform::Transform(glm::vec3 pos) {
	Transform::position = pos;
	Transform::rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	Transform::rotationAngle = 0.0f;
	Transform::scale = glm::vec3(1.0f);
	Transform::recalculateMatrix();
}
Transform::Transform(glm::vec3 pos, glm::vec3 rotAxis, float rotAngle) {
	Transform::position = pos;
	Transform::rotationAxis = rotAxis;
	Transform::rotationAngle = rotAngle;
	Transform::scale = glm::vec3(1.0f);
	Transform::recalculateMatrix();
}
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