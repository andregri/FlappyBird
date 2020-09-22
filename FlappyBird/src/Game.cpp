#include "Game.h"

#include <iostream>
#include <stdlib.h>

#include "Shader.h"
#include "Error.h"

#include "imgui/imgui.h"

Game::Game(const GLFWwindow* window, const bool keys[])
	: m_Window(window), m_Keys(keys), m_Level(), m_Bird(keys), m_ScrollX(0), m_Index(0), m_Random(0),
	m_PlayerHasControl(true)
{
	//GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	for (int i = 0; i < 10; i += 2)
	{
		float r = (float)rand() / (float)RAND_MAX;
		float x = m_Index * 3.0f;
		float y = r * 4.0f;
		m_Pipes[i].SetPosition(m_OFFSET + x, y);
		m_Pipes[i + 1].SetPosition(m_OFFSET + x, y - 11.5f);
		m_Index += 2;
	}
}

Game::~Game()
{
}

void Game::OnUpdate()
{
	if (m_PlayerHasControl)
	{
		--m_ScrollX;
		m_Level.Update(m_ScrollX);
	}

	m_Bird.Update(m_PlayerHasControl);

	for (int i = 0; i < 10; i++)
		m_Pipes[i].Update(m_ScrollX);

	if ((-m_ScrollX) > 300 && (-m_ScrollX) % 120 == 0)
	{
		float r = (float)rand() / (float)RAND_MAX;
		float x = m_Index * 3.0f;
		float y = r * 4.0f;
		m_Pipes[m_Index % 10].SetPosition(m_OFFSET + x, y);
		m_Pipes[(m_Index + 1) % 10].SetPosition(m_OFFSET + x, y - 11.5f);
		m_Index += 2;
	}

	if (m_PlayerHasControl && Collision())
	{
		m_PlayerHasControl = false;
		m_Bird.Fall();
	}
}

void Game::OnRender()
{
	m_Level.Render();
	m_Bird.Render();
	for (int i = 0; i < 10; ++i)
	{
		m_Pipes[i].Render(i % 2 == 0);
	}
}

void Game::OnImGuiRender()
{
	
}

bool Game::Collision()
{
	float bx = -m_ScrollX * 0.05f;
	float bx0 = bx - m_Bird.size / 2.0f;
	float bx1 = bx + m_Bird.size / 2.0f;

	float by = m_Bird.GetPosition().y;
	float by0 = by - m_Bird.size / 2.0f;
	float by1 = by + m_Bird.size / 2.0f;

	for (int i = 0; i < 10; ++i)
	{
		float px0 = m_Pipes[i].GetPosition().x;
		float px1 = px0 + m_Pipes[i].width;

		float py0 = m_Pipes[i].GetPosition().y;
		float py1 = py0 + m_Pipes[i].height;

		if (bx1 > px0 && bx0 < px1)
			if (by1 > py0 && by0 < py1)
				return true;
	}
	return false;
}
