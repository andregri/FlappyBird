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
	void Render(bool isTop);

	void SetPosition(float x, float y) { m_Position.x = x; m_Position.y = y; }
	const glm::vec3& GetPosition() const { return m_Position; }

	const float width = 1.5f;
	const float height = 8.0f;

private:
	Shader m_Shader;
	Texture2D m_Texture;
	VertexArray m_VAO;

	glm::vec3 m_Position;
	const glm::mat4 m_Proj;

	int m_ScrollX;
};