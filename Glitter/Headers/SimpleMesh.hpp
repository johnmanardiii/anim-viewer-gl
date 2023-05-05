#pragma once

#include <glm/glm.hpp>
#include "Program.hpp"
#include "GLSL.hpp"
#include "IUpdatable.hpp"
#include <memory>

class SimpleMesh : public IUpdatable
{
public:
	SimpleMesh();
	~SimpleMesh();
	void Draw();
	void Update() override;

private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;
	unsigned int m_IndexCount;

	glm::mat4 m_ModelMatrix;
	glm::vec3 position;
	glm::vec3 rotation;

	std::shared_ptr<Program> m_program;
};