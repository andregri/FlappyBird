#pragma once

#include "VertexArray.h"
#include "Texture2D.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Bird
{
public:
	Bird();
	~Bird();

private:
	float SIZE = 1.0f;
	VertexArray m_Mesh;
	Texture2D m_Texture;
};

