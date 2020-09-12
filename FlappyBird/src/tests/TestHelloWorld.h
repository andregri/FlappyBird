#pragma once
#include "Test.h"

#include "Shader.h"

#include "GL/glew.h"

namespace test {

	class TestHelloWorld : public Test
	{
	public:
		TestHelloWorld();
		~TestHelloWorld();

		void OnRender() override;
		void OnImGuiRender() override;

	private:
		Shader m_Shader;
		GLuint m_VAO;
		GLuint m_VB;
		GLuint m_IB;
	};

}