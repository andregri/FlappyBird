#pragma once

#include <GL/glew.h>

#include "Shader.h"
#include "VertexArray.h"
#include "Texture2D.h"
#include "Bird.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Level
{
public:
	Level();
	~Level();

	void Update(int scroll_x);
	void Render();

	//void RenderPipes();

private:
	Shader m_BackgroundShader;
	VertexArray m_BackgroundVAO;
	Texture2D m_BackgroundTexture;
	int m_ScrollX;

	int m_Map;

	const glm::mat4 m_Projection;
};

