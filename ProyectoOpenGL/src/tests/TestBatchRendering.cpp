#include "TestBatchRendering.h"

#include <iostream>
#include "DebugMacros.h"
#include "GL/glew.h"
#include "imgui/imgui.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ProgramShader.h"
#include "Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace test
{

    TestBatchRendering::TestBatchRendering()
        : m_Projection(glm::ortho(0.0f, 640.0f, 0.0f, 480.f, -100.0f, 100.0f)),
        m_View(glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, 0.0f))),
        m_TranslationA(150, 300, 0),
        m_TranslationB(0, 0, 0),
        m_ProgramShader(new ProgramShader("resources/shaders/basic.vert", "resources/shaders/basic.frag")),
        m_VAO(new VertexArray())
    {

        float positions[40] = {
         -75.0f,    -75.0f, 0.0f,   0.0f,   0.0f, // 0 | pos, tex
          75.0f,    -75.0f, 0.0f,   1.0f,   0.0f, // 1 | pos, tex
          75.0f,    75.0f,  0.0f,   1.0f,   1.0f, // 2 | pos, tex
         -75.0f,    75.0f,  0.0f,   0.0f,   1.0f, // 3 | pos, tex

         -150.0f,   -150.0f,    0.0f,   0.0f,   0.0f, // 4 | pos, tex
          0.0f,     -150.0f,    0.0f,   1.0f,   0.0f, // 5 | pos, tex
          0.0f,     0.0f,       0.0f,   1.0f,   1.0f, // 6 | pos, tex
         -150.0f,   0.0f,        0.0f,   0.0f,   1.0f // 7 | pos, tex
        };

        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0,

            4, 5, 6,
            6, 7, 4
        };

        openGLCall(glEnable(GL_BLEND));
        openGLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        /* Vertex Array + Vertex Buffer */
        m_VBO = new VertexBuffer(positions, 8 * 5 * sizeof(float));
        VertexBufferLayout layout;
        layout.push(GL_FLOAT, 3);
        layout.push(GL_FLOAT, 2);
        m_VAO->addBuffer(*m_VBO, layout);

        /* Index Buffer */
        m_IBO = new IndexBuffer(indices, 12);

        /* Shaders */
        m_ProgramShader->bind();

        m_Texture = new Texture("resources/textures/flowersDrawing.png");
        m_Texture->bind(0);
        m_ProgramShader->setUniform1i("u_Texture", 0);

        m_VAO->unbind();
        m_VBO->unbind();
        m_IBO->unbind();
        m_ProgramShader->unbind();
        
	}

	TestBatchRendering::~TestBatchRendering() 
    {
        delete m_VAO;
        delete m_VBO;
        delete m_IBO;
        
        delete m_ProgramShader;
    }

	void TestBatchRendering::onUpdate(float deltaTime) {}

	void TestBatchRendering::onRender()
	{
		openGLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		//openGLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        m_ProgramShader->bind();

        // Voy a imprimir dos "objetos" cada uno con su mvp y comparten va y ib.
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
        glm::mat4 mvp = m_Projection * m_View * model;
        m_ProgramShader->setUniformMatrix4fv("u_MVP", mvp);
        renderer.draw(*m_VAO, *m_IBO, *m_ProgramShader);
	}

	void TestBatchRendering::onImGuiRender()
	{
        //ImGui::Text("This is some useful text.");
        ImGui::SliderFloat3("Translacion A", &m_TranslationA.x, 0.0f, 640.0f);
        //ImGui::SliderFloat3("Translacion B", &m_TranslationB.x, 0.0f, 640.0f);
        ImGui::Text("Media: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}