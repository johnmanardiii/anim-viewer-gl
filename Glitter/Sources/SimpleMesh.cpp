#include "SimpleMesh.hpp"
#include <glad/glad.h>
#include <iostream>
#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

SimpleMesh::SimpleMesh()
{
	// create a simple triangle as a test
	m_program = std::make_shared<Program>();

	//TODO: move this out into a "renderer" class
	m_program->setVerbose(true);
	m_program->setShaderNames(
		"../Glitter/Shaders/simple_vert.glsl",
		"../Glitter/Shaders/simple_frag.glsl");
	if (!m_program->init())
	{
		std::cerr << "One or more shaders failed to compile... exiting!" << std::endl;
		exit(1);
	}
	m_program->addUniform("P");
	m_program->addUniform("V");
	m_program->addUniform("M");
	m_program->addAttribute("vertPos");

	// hard code triangle attribute and set up vao and vbo for vertex positions
	float points[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

	// set up vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	position = glm::vec3(0.f);
	rotation = glm::vec3(0.f);
}

SimpleMesh::~SimpleMesh()
{

}

void SimpleMesh::Draw(Camera* camera)
{
	m_program->bind();
	glm::mat4 V = camera->GetV();
	glm::mat4 P = camera->GetP();
	glUniformMatrix4fv(m_program->getUniform("M"), 1, GL_FALSE, &m_ModelMatrix[0][0]);
	glUniformMatrix4fv(m_program->getUniform("V"), 1, GL_FALSE, &V[0][0]);
	glUniformMatrix4fv(m_program->getUniform("P"), 1, GL_FALSE, &P[0][0]);

	// draw the triangle manually here
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	m_program->unbind();
}

void SimpleMesh::Update(float dt)
{
	static double time = 0.0f;
	time += dt;
	rotation.x += dt;
	
	m_ModelMatrix = glm::translate(glm::mat4(1.f), position);
	m_ModelMatrix = glm::rotate(m_ModelMatrix, rotation.x, glm::vec3(1.f, 0.f, 0.f)) * m_ModelMatrix;
}

void SimpleMesh::SetPosition(glm::vec3 position)
{
	position = position;
}

void SimpleMesh::SetRotation(glm::vec3 rotation)
{
	rotation = rotation;
}
