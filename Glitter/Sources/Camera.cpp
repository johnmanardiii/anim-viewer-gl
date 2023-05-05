#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp> //translate, rotate, scale,


Camera::Camera()
{
	LoadDefaultCamera();
}



void Camera::Update(float dt)
{
	P = glm::perspective(fovy, aspect, near, far);
	V = glm::lookAt(position, lookAt, up);
}

void Camera::LoadDefaultCamera()
{
	// perspective matrix parameters
 	fovy = 90.f;
 	near = .1f;
	far = 100.f;

	// camera matrix parameters
	position = glm::vec3(0.f, 0.f, -5.f);
	lookAt = glm::vec3(0.f, 0.f, 0.f);
	up = glm::vec3(0.f, 1.f, 0.f);
}

/*
	needs to be called whenever the window is resized
	TODO: bind this to the window resize event
*/
void Camera::SetCameraAspect(float aspect)
{
	this->aspect = aspect;
}

