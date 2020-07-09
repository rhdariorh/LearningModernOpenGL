#include "TestClearColor.h"
#include "DebugMacros.h"
#include "GL/glew.h"
#include "imgui/imgui.h"

namespace test
{

	TestClearColor::TestClearColor()
		: m_ClearColor { 0.5f, 0.0f, 0.0f, 1.0f }
	{}

	TestClearColor::~TestClearColor() {}

	void TestClearColor::onUpdate(float deltaTime) {}

	void TestClearColor::onRender()
	{
		openGLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		openGLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::onImGuiRender()
	{
		//ImGui::Begin("Clear Color");
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
		//ImGui::End();
	}

}