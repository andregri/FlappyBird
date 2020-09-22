#include "Level.h"

#include <iostream>

#include "Error.h"


Level::Level()
	: m_Map(0), m_BackgroundShader("res/shaders/bg.vert.glsl", "res/shaders/bg.frag.glsl"),
	m_Projection(glm::ortho(-10.0f, 10.0f, -10.0f * 9.0f / 16.0f, 10.0f * 9.0f / 16.0f, -1.0f, 1.0f))
{
	float positions[] = {
		-10.0f, -10.0f * 9.0f / 16.0f, 0.0f,	// left - bottom
		-10.0f,  10.0f * 9.0f / 16.0f, 0.0f,	// left - top
		  0.0f,  10.0f * 9.0f / 16.0f, 0.0f,	// right - top
		  0.0f, -10.0f * 9.0f / 16.0f, 0.0f,	// right - bottom
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	float tex_coord[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	m_BackgroundShader.Bind();

	m_BackgroundVAO = VertexArray(4, positions, tex_coord, 6, indices);
	m_BackgroundTexture = Texture2D("res/textures/bg.png");

	m_BackgroundShader.Unbind();

	//CreatePipes();
}


Level::~Level()
{
}


void Level::Update(int scroll_x)
{
	m_ScrollX = scroll_x;
	if ((-m_ScrollX) % 300 == 0) m_Map++;
}

void Level::Render()
{
	m_BackgroundShader.Bind();
	m_BackgroundTexture.Bind();

	GLCall(glUniformMatrix4fv(m_BackgroundShader.GetUniformLocation("u_proj"), 1, GL_FALSE, &m_Projection[0][0]));

	for (int i = m_Map; i < m_Map + 4; ++i)
	{
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(i * 10 + m_ScrollX * 0.035f, 0, 0));
		GLCall(glUniformMatrix4fv(m_BackgroundShader.GetUniformLocation("u_view"), 1, GL_FALSE, &view[0][0]));
		m_BackgroundVAO.Render();
	}
}
