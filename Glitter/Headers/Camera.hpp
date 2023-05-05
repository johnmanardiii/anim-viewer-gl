#pragma once

#include <glm/glm.hpp>
#include "IUpdatable.hpp"

/*
	Represents a camera in 3D space
	TODO: extend this to support input events
*/
class Camera : public IUpdatable
{
public:
	Camera();
	void Update(float dt);
	void LoadDefaultCamera();
	void SetCameraAspect(float aspect);
	glm::mat4 GetP() const { return P; }
	glm::mat4 GetV() const { return V; }

	// perspective matrix parameters
	float fovy;
	float aspect;
	float near;
	float far;

	// camera matrix parameters
	glm::vec3 position;
	glm::vec3 lookAt;
	glm::vec3 up;

private:
	glm::mat4 P;
	glm::mat4 V;
};