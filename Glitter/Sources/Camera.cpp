#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp> //translate, rotate, scale,


Camera::Camera()
{
	LoadDefaultCamera();
}

void Camera::Update(float dt)
{
	P = glm::perspective(fovy, aspect, nearDist, farDist);
	V = glm::lookAt(position, center, up);
}

void Camera::LoadDefaultCamera()
{
	// perspective matrix parameters
 	fovy = glm::radians(90.0f);
 	nearDist = .1f;
	farDist = 100.f;

	// camera matrix parameters
	position = glm::vec3(0.f, 0.f, 5.f);
	center = glm::vec3(0.f, 0.f, 0.f);
	up = glm::vec3(0.f, 1.f, 0.f);
}

/*
	needs to be called whenever the window is resized
	TODO: bind this to the window resize event
*/
void Camera::SetCameraAspect(float aspectTarget)
{
	this->aspect = aspectTarget;
}

