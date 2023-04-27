#pragma once

#include "glm/glm.hpp"
#include <vector>

/*
	Class for containing the data of an animated model.
	Has the capability for rendering itself when passed a reference to a renderer.

	Contains a list of meshes, and a list of animations.
	Has a string for it's status

	Currently:
	- only contains a list of vertices in the model
*/
class AnimatedModel
{
public:
	AnimatedModel();
	~AnimatedModel();

private:
	std::vector<int> m_vertexIndices;
	std::vector<glm::vec3> m_vertices;
};