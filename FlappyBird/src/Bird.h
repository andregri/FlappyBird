#pragma once

#include "VertexArray.h"
#include "Texture2D.h"
#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Bird
{
public:
	Bird(const bool keys[]);
	~Bird();

	void Update(bool playerHasControl);
	void Render();

	void Fall();

	const float size = 1.0f;
	const glm::vec3& GetPosition() const { return m_Position; }

private:
	Shader m_Shader;
	VertexArray m_Mesh;
	Texture2D m_Texture;
	glm::vec3 m_Position;
	float m_Rotation;
	float m_DeltaY = -0.15f;
	const bool * m_Keys;
};

