#pragma once

#include <array>

#include "Shader.h"
#include "Level.h"

#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Game
{
public:
	Game(const GLFWwindow* m_Window, const bool keys[]);
	~Game();

	void OnUpdate();
	void OnRender();
	void OnImGuiRender();

private:
	const GLFWwindow* m_Window;
	const bool* const m_Keys;

	Shader m_BackgroundShader;
	Level m_Level;

	glm::mat4 m_Proj = glm::ortho(-10.0f, 10.0f, -10.0f * 9.0f / 16.0f, 10.0f * 9.0f / 16.0f, -1.0f, 1.0f);
};

