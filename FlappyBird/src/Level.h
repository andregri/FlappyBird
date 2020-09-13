#pragma once

#include <GL/glew.h>

#include "Shader.h"
#include "VertexArray.h"
#include "Texture2D.h"

class Level
{
public:
	Level(Shader * shader);
	~Level();

	void Update();
	void Render();

private:
	Shader * m_BackgroundShader;
	VertexArray m_BackgroundVAO;
	Texture2D m_BackgroundTexture;

	int m_ScrollX;
	int m_Map;
};

