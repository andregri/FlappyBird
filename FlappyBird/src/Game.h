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

	bool Collision();

private:
	const GLFWwindow* m_Window;
	const bool* const m_Keys;

	Level m_Level;
	int m_ScrollX;

	Bird m_Bird;

	Pipe m_Pipes[10];
	int m_Index;
	int m_Random;

	bool m_PlayerHasControl;

	const int m_OFFSET = 5.0f;
};
