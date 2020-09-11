#pragma once
#include "Test.h"

#include <vector>

namespace test {

	class TestMenu : public Test
	{
	public:
		TestMenu();
		~TestMenu();
		void OnRender() override;
		void OnImGuiRender() override;

		template <typename T>
		void RegisterTest(const std::string & name)
		{
			m_Tests.push_back(std::make_pair(name, new T()));
		}

	private:
		Test* m_CurrentTest;
		std::vector<std::pair<std::string, Test*>> m_Tests;
	};

}