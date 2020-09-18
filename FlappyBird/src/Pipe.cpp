#include "Pipe.h"


Pipe::Pipe()
	: m_Shader("res/shaders/pipe.vert.glsl", "res/shaders/pipe.frag.glsl"),
	m_Position(0.0f, 0.0f, 0.0f),
	m_Proj(glm::ortho(-10.0f, 10.0f, -10.0f * 9.0f / 16.0f, 10.0f * 9.0f / 16.0f, -1.0f, 1.0f))
{
	float positions[] = {
		0.0f,	 0.0f,     0.0f,	// left - bottom
		0.0f,	 m_Height, 0.0f,	// left - top
		m_Width, m_Height, 0.0f,	// right - top
		m_Width, 0.0f,	   0.0f,	// right - bottom
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

	m_VAO = VertexArray(4, positions, tex_coord, 6, indices);
	m_Texture = Texture2D("res/textures/pipe.png");

	GLCall(glActiveTexture(GL_TEXTURE1));

	m_Shader.Bind();
	GLCall(glUniform1i(m_Shader.GetUniformLocation("tex"), 1));
	m_Shader.Unbind();
}


Pipe::~Pipe()
{
}

void Pipe::Update(int scroll_x)
{
	m_ScrollX = scroll_x;
}

void Pipe::Render()
{
	m_Shader.Bind();

	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(m_ScrollX * 0.035f, 0, 0));
	GLCall(glUniformMatrix4fv(m_Shader.GetUniformLocation("u_view"), 1, GL_FALSE, &view[0][0]));
	GLCall(glUniformMatrix4fv(m_Shader.GetUniformLocation("u_proj"), 1, GL_FALSE, &m_Proj[0][0]));
		
	m_Texture.Bind();
	m_VAO.Bind();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Position);
	GLCall(glUniformMatrix4fv(m_Shader.GetUniformLocation("u_model"), 1, GL_FALSE, &model[0][0]));
	m_VAO.Draw();

	m_Texture.Unbind();
	m_VAO.Unbind();

	m_Shader.Unbind();
}

