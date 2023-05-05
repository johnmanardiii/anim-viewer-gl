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
	virtual void Update(float dt) override;
	void LoadDefaultCamera();
	void SetCameraAspect(float aspectTarget);
	glm::mat4 GetP() const { return P; }
	glm::mat4 GetV() const { return V; }

	// perspective matrix parameters
	float fovy;
	float aspect;
	float nearDist;
	float farDist;

	// camera matrix parameters
	glm::vec3 position;
	glm::vec3 center;
	glm::vec3 up;

private:
	glm::mat4 P;
	glm::mat4 V;
};