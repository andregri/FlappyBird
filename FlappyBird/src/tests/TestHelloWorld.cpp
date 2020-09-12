#include "TestHelloWorld.h"

#include "Shader.h"

#include "GL/glew.h"
#include "imgui/imgui.h"

namespace test {

	TestHelloWorld::TestHelloWorld()
		: m_VAO(0),
		m_Shader("src/tests/test_shaders/vertex.shader.glsl", "src/tests/test_shaders/fragment.shader.glsl")
	{
		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.8f, 1.0f,
			 0.5f,  0.5f, 0.0f, 0.2f, 0.8f, 0.8f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.2f, 0.8f, 0.8f, 1.0f };
		
		unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		GLuint program = m_Shader.GetRendererID();

		glCreateVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VB);
		glBindBuffer(GL_ARRAY_BUFFER, m_VB);
		glBufferData(GL_ARRAY_BUFFER, 4 * 7 * sizeof(float), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &m_IB);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		glBindAttribLocation(program, 0, "a_Position");
		glBindAttribLocation(program, 1, "a_Color");

		GLint position_attrib_index = glGetAttribLocation(program, "a_Position");
		glEnableVertexAttribArray(position_attrib_index);
		glVertexAttribPointer(position_attrib_index, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);

		GLint color_attrib_index = glGetAttribLocation(program, "a_Color");
		glEnableVertexAttribArray(color_attrib_index);
		glVertexAttribPointer(color_attrib_index, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(3 * sizeof(float)));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


	TestHelloWorld::~TestHelloWorld()
	{
		glDeleteBuffers(1, &m_VB);
		glDeleteVertexArrays(1, &m_VAO);
	}

	void TestHelloWorld::OnRender()
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(m_Shader.GetRendererID());
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		glBindVertexArray(0);
		glUseProgram(0);
	}

	void TestHelloWorld::OnImGuiRender()
	{
		ImGui::Text("Hello World!");
		OnRender();
	}

}