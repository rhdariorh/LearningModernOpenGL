#include "Test.h"
#include "imgui/imgui.h"
#include "DebugMacros.h"
#include "GL/glew.h"

namespace test
{

	TestMenu::TestMenu(Test*& currentTestPointer)
		: m_CurrentTest(currentTestPointer)
	{}

	void TestMenu::onRender()
	{
		openGLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	}

	void TestMenu::onImGuiRender()
	{
		for (std::pair<std::string, std::function<Test* ()>>& test : m_Tests ) // Podría usar auto&
		{
			if (ImGui::Button(test.first.c_str()))
				m_CurrentTest = test.second();
		}
	}

}