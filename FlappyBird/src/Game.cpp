#include "Game.h"

#include <iostream>

#include "Shader.h"
#include "Error.h"

#include "imgui/imgui.h"

Game::Game(const GLFWwindow* window, const bool keys[])
	: m_Window(window), m_Keys(keys), m_Level(), m_Bird(keys), m_ScrollX(0), m_Index(0)
{
	//GLCall(glEnable(GL_DEPTH_TEST));
	//GLCall(glEnable(GL_BLEND));
	//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	for (int i = 0; i < 10; i += 2)
	{
		m_Pipes[i].SetPosition(m_Index * 3.0f, 4.0f);
		m_Pipes[i + 1].SetPosition(m_Index * 3.0f, 4.0f - 10.0f);
		m_Index += 2;
	}
}

Game::~Game()
{
}

void Game::OnUpdate()
{
	--m_ScrollX;
	m_Level.Update(m_ScrollX);

	m_Bird.Update();

	for (int i = 0; i < 10; ++i)
	{
		m_Pipes[i].Update(m_ScrollX);
	}
}

void Game::OnRender()
{
	m_Level.Render();
	m_Bird.Render();
	for (int i = 0; i < 10; ++i)
	{
		m_Pipes[i].Render();
	}
}

void Game::OnImGuiRender()
{
	
}
