#include "Bird.h"

#include <GLFW/glfw3.h>


Bird::Bird(const bool keys[])
	: m_Shader("res/shaders/bird.vert.glsl", "res/shaders/bird.frag.glsl"), m_Keys(keys)
{
	float positions[] = {
		-SIZE / 2.0f, -SIZE / 2.0f, 0.0f,	// left - bottom
		-SIZE / 2.0f,  SIZE / 2.0f, 0.0f,	// left - top
		 SIZE / 2.0f,  SIZE / 2.0f, 0.0f,	// right - top
		 SIZE / 2.0f, -SIZE / 2.0f, 0.0f,	// right - bottom
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

	m_Mesh = VertexArray(4, positions, tex_coord, 6, indices);
	m_Texture = Texture2D("res/textures/bird.png");

	GLCall(glActiveTexture(GL_TEXTURE1));

	m_Shader.Bind();
	GLCall(glUniform1i(m_Shader.GetUniformLocation("tex"), 1));
	m_Shader.Unbind();
}


Bird::~Bird()
{
}

void Bird::Update()
{
	m_Position.y -= m_DeltaY;

	if (m_Keys[GLFW_KEY_SPACE])
		m_DeltaY = -0.15f;
	else
		m_DeltaY += 0.01f;

	m_Rotation = -m_DeltaY * 2.0f;
}

void Bird::Fall()
{
	m_DeltaY = -0.15f;
}

void Bird::Render()
{
	m_Shader.Bind();

	glm::mat4 proj = glm::ortho(-10.0f, 10.0f, -10.0f * 9.0f / 16.0f, 10.0f * 9.0f / 16.0f, -1.0f, 1.0f);
	GLCall(glUniformMatrix4fv(m_Shader.GetUniformLocation("u_proj"), 1, GL_FALSE, &proj[0][0]));
	glm::mat4 translationY = glm::translate(glm::mat4(1.0f), m_Position);
	glm::mat4 model = glm::rotate(translationY, m_Rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	GLCall(glUniformMatrix4fv(m_Shader.GetUniformLocation("u_model"), 1, GL_FALSE, &model[0][0]));
	m_Texture.Bind();
	m_Mesh.Render();
	m_Shader.Unbind();
}
