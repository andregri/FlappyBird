#pragma once

#include <GL/glew.h>

#include "Shader.h"
#include "Texture2D.h"
#include "VertexArray.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Pipe
{
public:
	Pipe();
	~Pipe();

	void Update(int scroll_x);
	void Render();

	void SetPosition(float x, float y) { m_Position.x = x; m_Position.y = y; }

private:
	Shader m_Shader;
	Texture2D m_Texture;
	VertexArray m_VAO;

	glm::vec3 m_Position;
	const glm::mat4 m_Proj;

	int m_ScrollX;

	const float m_Width = 1.5f;
	const float m_Height = 8.0f;
};

