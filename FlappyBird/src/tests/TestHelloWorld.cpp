#include "TestHelloWorld.h"

#include "imgui/imgui.h"

namespace test {

	TestHelloWorld::TestHelloWorld()
	{
	}


	TestHelloWorld::~TestHelloWorld()
	{
	}

	void TestHelloWorld::OnImGuiRender()
	{
		ImGui::Text("Hello World!");
	}

}