#pragma once

#include "Test.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ProgramShader.h"

namespace test {
	class TestBatchRendering2 : public Test
	{
	private:
		VertexArray* m_VAO;
		VertexBuffer* m_VBO;
		IndexBuffer* m_IBO;
		ProgramShader* m_ProgramShader;
		Texture* m_Textures[32];

		glm::mat4 m_Projection, m_View;
		glm::vec3 m_TranslationA, m_TranslationB;

	public:
		TestBatchRendering2();
		~TestBatchRendering2();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	};

}

