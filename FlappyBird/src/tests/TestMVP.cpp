#include "TestMVP.h"

#include "Shader.h"

#include "GL/glew.h"

#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

	TestMVP::TestMVP()
		: m_VAO(0), m_TranslationA(200, 200, 0),
		m_Shader("src/tests/test_shaders/vert.glsl", "src/tests/test_shaders/frag.glsl")
	{
		float vertices[] = {
			-50.0f, -50.0f, 0.0f, 0.2f, 0.8f, 0.8f, 1.0f,
			 50.0f, -50.0f, 0.0f, 0.2f, 0.8f, 0.8f, 1.0f,
			 50.0f,  50.0f, 0.0f, 0.2f, 0.8f, 0.8f, 1.0f,
			-50.0f,  50.0f, 0.0f, 0.2f, 0.8f, 0.8f, 1.0f };

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


	TestMVP::~TestMVP()
	{
		glDeleteBuffers(1, &m_VB);
		glDeleteVertexArrays(1, &m_VAO);
	}

	void TestMVP::OnRender()
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(m_Shader.GetRendererID());
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);

		glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
		glm::mat4 mvp = proj * view * model;  // the order is important!
		int location = glGetUniformLocation(m_Shader.GetRendererID(), "u_MVP");
		glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		glBindVertexArray(0);
		glUseProgram(0);
	}

	void TestMVP::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translate A", &m_TranslationA.x, 0.0f, 1280.0f);
		OnRender();
	}

}