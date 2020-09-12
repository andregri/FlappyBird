#pragma once
#include "Test.h"

#include "Shader.h"

namespace test {

	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnRender() override;
		void OnImGuiRender() override;

	private:
		Shader m_Shader;
		GLuint m_VAO;
		GLuint m_VB;
		GLuint m_IB;
		GLuint m_Texture;
	};

}