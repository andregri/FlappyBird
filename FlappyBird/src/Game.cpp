#include "Game.h"

#include <iostream>

#include "Shader.h"
#include "Error.h"

#include "imgui/imgui.h"

Game::Game(const GLFWwindow* window, const bool keys[])
	: m_Window(window), m_Keys(keys),
	m_BackgroundShader("res/shaders/bg.vert.glsl", "res/shaders/bg.frag.glsl"),
	m_Level(&m_BackgroundShader)
{
	//GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

Game::~Game()
{
}

void Game::OnUpdate()
{
	m_Level.Update();
}

void Game::OnRender()
{
	m_BackgroundShader.Bind();
	GLCall(glUniformMatrix4fv(m_BackgroundShader.GetUniformLocation("u_proj"), 1, GL_FALSE, &m_Proj[0][0]));
	m_Level.Render();
	m_BackgroundShader.Unbind();
}

void Game::OnImGuiRender()
{
	
}
