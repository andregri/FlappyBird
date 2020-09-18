#pragma once

#include <array>

#include "Level.h"
#include "Bird.h"
#include "Pipe.h"

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

	Level m_Level;
	int m_ScrollX;

	Bird m_Bird;

	Pipe m_Pipe;
};

