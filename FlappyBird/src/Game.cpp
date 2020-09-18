#include "Game.h"

#include <iostream>

#include "Shader.h"
#include "Error.h"

#include "imgui/imgui.h"

Game::Game(const GLFWwindow* window, const bool keys[])
	: m_Window(window), m_Keys(keys), m_Level(), m_Bird(keys), m_ScrollX(0)
{
	//GLCall(glEnable(GL_DEPTH_TEST));
	//GLCall(glEnable(GL_BLEND));
	//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

Game::~Game()
{
}

void Game::OnUpdate()
{
	m_Level.Update(--m_ScrollX);
	m_Bird.Update();

	m_Pipe.Update(m_ScrollX);
	m_Pipe.SetPosition(3.0f, 4.0f);
}

void Game::OnRender()
{
	m_Level.Render();
	m_Bird.Render();
	m_Pipe.Render();
}

void Game::OnImGuiRender()
{
	
}
