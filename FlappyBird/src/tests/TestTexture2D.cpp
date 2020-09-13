#include "TestTexture2D.h"

#include <iostream>
#include <stdexcept>

#include "Shader.h"

#include "GL/glew.h"
#include "imgui/imgui.h"

#include "stb_image/stb_image.h"

namespace test {

	TestTexture2D::TestTexture2D()
		: m_Shader("src/tests/test_shaders/vertex.shader.glsl", "src/tests/test_shaders/fragment.shader.glsl")
	{
		float vertices[] = {
			// positions			// colors					// texture coords
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 0.0f, 0.0f,		1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 0.0f, 0.0f,		0.0f, 1.0f };

		unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLuint program = m_Shader.GetRendererID();

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VB);
		glBindBuffer(GL_ARRAY_BUFFER, m_VB);
		glBufferData(GL_ARRAY_BUFFER, 4 * 9 * sizeof(float), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &m_IB);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		glBindAttribLocation(program, 0, "a_Position");
		glBindAttribLocation(program, 1, "a_Color");
		glBindAttribLocation(program, 2, "a_TexCoord");

		GLint position_attrib_index = glGetAttribLocation(program, "a_Position");
		GLint color_attrib_index = glGetAttribLocation(program,	   "a_Color");
		GLint texcoord_attrib_index = glGetAttribLocation(program, "a_TexCoord");

		glEnableVertexAttribArray(position_attrib_index);
		glEnableVertexAttribArray(color_attrib_index);
		glEnableVertexAttribArray(texcoord_attrib_index);

		glVertexAttribPointer(position_attrib_index, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
		glVertexAttribPointer(color_attrib_index,	 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
		glVertexAttribPointer(texcoord_attrib_index, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));

		// Load the texture
		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, n_channels;
		stbi_set_flip_vertically_on_load(1);
		unsigned char* data = stbi_load("res/textures/flappy_bird.png", &width, &height, &n_channels, 4);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			std::cerr << "Failed to load the texture.\n";
		}
		stbi_image_free(data);

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


	TestTexture2D::~TestTexture2D()
	{
		glDeleteTextures(1, &m_Texture);
		glDeleteBuffers(1, &m_VB);
		glDeleteBuffers(1, &m_IB);
		glDeleteVertexArrays(1, &m_VAO);
	}

	void TestTexture2D::OnRender()
	{
		glUseProgram(m_Shader.GetRendererID());
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);
		glBindTexture(GL_TEXTURE_2D, m_Texture);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}

	void TestTexture2D::OnImGuiRender()
	{
		OnRender();
	}

}