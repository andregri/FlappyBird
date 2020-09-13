#include "TestMenu.h"

#include "imgui/imgui.h"

#include <vector>
#include <string>

namespace test {

	TestMenu::TestMenu()
		: m_CurrentTest(nullptr)
	{
	}


	TestMenu::~TestMenu()
	{
		for (auto test : m_Tests)
		{
			delete test.second;
		}
	}

	void TestMenu::OnRender()
	{
	}

	void TestMenu::OnImGuiRender()
	{
		ImGui::Begin("Test");

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		if (m_CurrentTest)
		{
			if (ImGui::Button("<-")) m_CurrentTest = nullptr;
			else m_CurrentTest->OnImGuiRender();
		}
		else
		{
			for (auto test : m_Tests)
				if (ImGui::Button(test.first.c_str())) m_CurrentTest = test.second;
		}
		
		ImGui::End();
	}

}