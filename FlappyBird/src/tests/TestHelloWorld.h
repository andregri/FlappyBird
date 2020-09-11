#pragma once
#include "Test.h"

namespace test {

	class TestHelloWorld : public Test
	{
	public:
		TestHelloWorld();
		~TestHelloWorld();

		void OnImGuiRender() override;
	};

}