/**
 * @file TestBatchRenderDynamicGeoIndices.cpp
 * @brief Resumen
 *
 *  Descripcion
 *
 * @author Darío Rodríguez Hernández
 * @date 00/00/0000
 * @version 0.0
 */

#include "TestBatchRenderDynamicGeoIndices.h"
#include <iostream>
#include <array>
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
    struct Vec2 {
        float x, y;
    };
    struct Vec3 {
        float x, y, z;
    };
    struct Vec4 {
        float x, y, z, w;
    };

    struct Vertex
    {
        Vec3 position;
        Vec4 color;
        Vec2 texCoords;
        float texIndex;
    };

    // Returns the position inside the buffer that is up to
    static Vertex* CreateQuad(Vertex* target, float x, float y, float size, float texIndex) 
    {

        target->position = { x, y, 0.0f };
        target->color = { 1.0f,  0.5f, 0.7f, 0.8f };
        target->texCoords = { 0.0f, 0.0f };
        target->texIndex = texIndex;
        target++; // Increment the buffer pointer

        target->position = { x + size, y, 0.0f };
        target->color = { 1.0f,  0.5f, 0.7f, 0.8f };
        target->texCoords = { 1.0f, 0.0f };
        target->texIndex = texIndex;
        target++;

        target->position = { x + size, y + size, 0.0f };
        target->color = { 1.0f,  0.5f, 0.7f, 0.8f };
        target->texCoords = { 1.0f, 1.0f };
        target->texIndex = texIndex;
        target++;

        target->position = { x, y + size, 0.0f };
        target->color = { 1.0f,  0.5f, 0.7f, 0.8f };
        target->texCoords = { 0.0f, 1.0f };
        target->texIndex = texIndex;
        target++;

        return target;
    }

    TestBatchRenderDynamicGeoIndices::TestBatchRenderDynamicGeoIndices()
        : m_Projection(glm::ortho(0.0f, 640.0f, 0.0f, 480.f, -100.0f, 100.0f)),
        m_View(glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, 0.0f))),
        m_TranslationA(150, 300, 0),
        m_TranslationB(0, 0, 0),
        m_ProgramShader(new ProgramShader("resources/shaders/basicColor.vert", "resources/shaders/basicColor.frag")),
        m_VAO(new VertexArray())
    {

        const unsigned int MaxQuadCount = 1000; // Quizá habría sido mejor usar size_t en vez de unsigned int en todos lados.
        const unsigned int MaxVertexCount = MaxQuadCount * 4;
        const unsigned int MaxIndexCount = MaxQuadCount * 6;

        
        /*unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0,

            4, 5, 6,
            6, 7, 4
        };*/

        unsigned int indices[MaxIndexCount];
        unsigned int offset = 0;
        for (unsigned int i = 0; i < MaxIndexCount; i += 6)
        {
            indices[i + 0] = 0 + offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 2 + offset;
            
            indices[i + 3] = 2 + offset;
            indices[i + 4] = 3 + offset;
            indices[i + 5] = 0 + offset;

            offset += 4;
        }


        openGLCall(glEnable(GL_BLEND));
        openGLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        /* Vertex Array + Vertex Buffer */
        m_VBO = new VertexBuffer(nullptr, sizeof(Vertex) * MaxVertexCount, GL_DYNAMIC_DRAW);
        VertexBufferLayout layout;
        layout.push(GL_FLOAT, 3);
        layout.push(GL_FLOAT, 4);
        layout.push(GL_FLOAT, 2);
        layout.push(GL_FLOAT, 1);
        m_VAO->addBuffer(*m_VBO, layout);

        /* Index Buffer */
        m_IBO = new IndexBuffer(indices, MaxIndexCount);

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

	TestBatchRenderDynamicGeoIndices::~TestBatchRenderDynamicGeoIndices() 
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

	void TestBatchRenderDynamicGeoIndices::onUpdate(float deltaTime) 
    {
        std::array<Vertex, 1000> vertices;
        Vertex* buffer = vertices.data();

        unsigned int indexCount = 0;
        for (unsigned int y = 0; y < 5; y++)
        {
            for (unsigned int x = 0; x < 5; x++)
            {
               buffer = CreateQuad(buffer, x * 50, y * 50, 50.0f * deltaTime, (x + y) % 2);
               indexCount += 6;
            }
        }
        
        buffer = CreateQuad(buffer, -75.0f, -75.0f, 150.0f * deltaTime, 0.0f);
        indexCount += 6;

        m_IBO->setCount(indexCount);

        // Set dynamic vertex buffer
        m_VBO->bind();
        m_VBO->setData(vertices.data(), vertices.size() * sizeof(Vertex));

        // MVP transformation
        m_ProgramShader->bind();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
        glm::mat4 mvp = m_Projection * m_View * model;

        m_ProgramShader->setUniformMatrix4fv("u_MVP", mvp);
    }

	void TestBatchRenderDynamicGeoIndices::onRender()
	{
        openGLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
        //openGLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;
        renderer.draw(*m_VAO, *m_IBO, *m_ProgramShader);
	}

	void TestBatchRenderDynamicGeoIndices::onImGuiRender()
	{
        //ImGui::Text("This is some useful text.");
        ImGui::SliderFloat3("Translacion A", &m_TranslationA.x, 0.0f, 640.0f);
        //ImGui::SliderFloat3("Translacion B", &m_TranslationB.x, 0.0f, 640.0f);
        ImGui::Text("Media: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}