#pragma once

#include <vector>
#include <unordered_map>

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
	virtual void update(std::unordered_map<int, bool> keys, float mouseDx, float mouseDy, float dt);

	float aspectRatio;
	float fov;

	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 worldUp;

	glm::mat4 matrix;
};

class FreeCamera : public Camera {
private:
	float pitch = 0.0f;
	float yaw = -90.0f;
public:
	FreeCamera() : Camera() {}
	FreeCamera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up) : Camera(pos, dir, up) {}
	FreeCamera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, float ratio, float fov) : Camera(pos, dir, up, ratio, fov) {}

	float moveSpeed = 2.0f;
	float mouseSensitivity = 0.04f;

	void update(std::unordered_map<int, bool> keys, float mouseDx, float mouseDy, float dt) override;
};