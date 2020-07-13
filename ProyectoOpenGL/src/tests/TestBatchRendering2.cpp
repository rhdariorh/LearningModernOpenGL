#include "TestBatchRendering2.h"

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

    TestBatchRendering2::TestBatchRendering2()
        : m_Projection(glm::ortho(0.0f, 640.0f, 0.0f, 480.f, -100.0f, 100.0f)),
        m_View(glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, 0.0f))),
        m_TranslationA(150, 300, 0),
        m_TranslationB(0, 0, 0),
        m_ProgramShader(new ProgramShader("resources/shaders/basicColor.vert", "resources/shaders/basicColor.frag")),
        m_VAO(new VertexArray())
    {

        float positions[80] = { // pos[3], color[4], tex[2], texIndex
         -75.0f, -75.0f,  0.0f,     1.0f,  0.5f, 0.7f, 0.8f,    0.0f, 0.0f,  0.0f, // 0
          75.0f, -75.0f,  0.0f,     1.0f,  0.5f, 0.7f, 0.8f,    1.0f, 0.0f,  0.0f, // 1
          75.0f,  75.0f,  0.0f,     1.0f,  0.5f, 0.7f, 0.8f,    1.0f, 1.0f,  0.0f, // 2
         -75.0f,  75.0f,  0.0f,     1.0f,  0.5f, 0.7f, 0.8f,    0.0f, 1.0f,  0.0f, // 3

         -150.0f, -150.0f,  0.0f,   0.2f,  0.8f, 0.6f, 0.8f,    0.0f, 0.0f,  1.0f, // 4
          0.0f,   -150.0f,  0.0f,   0.2f,  0.8f, 0.6f, 0.8f,    1.0f, 0.0f,  1.0f, // 5
          0.0f,    0.0f,    0.0f,   0.2f,  0.8f, 0.6f, 0.8f,    1.0f, 1.0f,  1.0f, // 6
         -150.0f,  0.0f,    0.0f,   0.2f,  0.8f, 0.6f, 0.8f,    0.0f, 1.0f,  1.0f  // 7
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
        m_VBO = new VertexBuffer(positions, 8 * 10 * sizeof(float));
        VertexBufferLayout layout;
        layout.push(GL_FLOAT, 3);
        layout.push(GL_FLOAT, 4);
        layout.push(GL_FLOAT, 2);
        layout.push(GL_FLOAT, 1);
        m_VAO->addBuffer(*m_VBO, layout);

        /* Index Buffer */
        m_IBO = new IndexBuffer(indices, 12);

        /* Shaders */
        m_ProgramShader->bind();
        m_ProgramShader->setUniform4f("u_Color", 1.0f, 0.7f, 0.2f, 0.5f);

        m_Textures[0] = new Texture("resources/textures/flowersDrawing.png");
        m_Textures[1] = new Texture("resources/textures/tex2.png");
        m_Textures[0]->bind(0);
        m_Textures[1]->bind(1);

        int texIndices[2] = { 0, 1 };
        m_ProgramShader->setUniform1iv("u_Textures", 2, texIndices);

        //Texture::unbind();
        m_VAO->unbind();
        m_VBO->unbind();
        m_IBO->unbind();
        m_ProgramShader->unbind();
	}

	TestBatchRendering2::~TestBatchRendering2() 
    {
        // delete textures
        for (unsigned int i = 0; i < 32; i++)
        {
            delete m_Textures[i];
        }

        delete m_VAO;
        delete m_VBO;
        delete m_IBO;
        
        delete m_ProgramShader;
    }

	void TestBatchRendering2::onUpdate(float deltaTime) {}

	void TestBatchRendering2::onRender()
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

	void TestBatchRendering2::onImGuiRender()
	{
        //ImGui::Text("This is some useful text.");
        ImGui::SliderFloat3("Translacion A", &m_TranslationA.x, 0.0f, 640.0f);
        //ImGui::SliderFloat3("Translacion B", &m_TranslationB.x, 0.0f, 640.0f);
        ImGui::Text("Media: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}