#pragma once
#include "Test.h"

#include "Shader.h"

#include "GL/glew.h"

#include "glm/glm.hpp"

namespace test {

	class TestMVP : public Test
	{
	public:
		TestMVP();
		~TestMVP();

		void OnRender() override;
		void OnImGuiRender() override;

	private:
		Shader m_Shader;
		GLuint m_VAO;
		GLuint m_VB;
		GLuint m_IB;

		glm::vec3 m_TranslationA;
	};

}