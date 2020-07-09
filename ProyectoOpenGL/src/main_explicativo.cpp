/**
 * @file main_explicativo.cpp
 * @brief main antiguo con explicaciones
 * Programa principal explicativo.
 * 
 * Se crean vertes array, vertex buffer, index buffer, shader
 *
 * @author Darío Rodríguez Hernández
 * @date 00/00/0000
 * @version 0.0
 */

//Debug format:
//    [X Error](location): error name/description.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

// Mis clases
#include "DebugMacros.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ProgramShader.h"
#include "Texture.h"



/*
* Función principal
*/
int main(void)
{
    //////////////////////////////////////////////////////////////////////////////////////
    GLFWwindow* window;
    /********************/
    /* INICIALIZACIONES */
    /********************/
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creea una ventana en modo ventana y si contexto de OpenGL
    window = glfwCreateWindow(640, 480, "My window :)", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Hace actual el contexto de la ventana
    glfwMakeContextCurrent(window);

    // Para controlar el framerate
    glfwSwapInterval(1);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "[GLEW Error]: %s\n", glewGetErrorString(err));
    }

    // Imprimir información inicial
    std::cout << "Versions:\n";
    std::cout << "---OpenGL:\t" << glGetString(GL_VERSION) << std::endl;
    std::cout << "---GLSL:\t" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "---GLFW:\t" << glfwGetVersionString() << std::endl;
    std::cout << "---GLEW:\t" << glewGetString(GLEW_VERSION) << std::endl << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////

    /*******************/
    /* PARTE PRINCIPAL */
    /*******************/

    {
        /* Geometrias */
        float positions[16] = {
             -75.0f,   -75.0f,  0.0f, 0.0f, // 0 | pos, tex
              75.0f,   -75.0f,  1.0f, 0.0f, // 1 | pos, tex
              75.0f,    75.0f,  1.0f, 1.0f, // 2 | pos, tex
             -75.0f,    75.0f,  0.0f, 1.0f  // 3 | pos, tex
        };

        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        openGLCall(glEnable(GL_BLEND));
        openGLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        /* Vertex Array + Vertex Buffer */
        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.push(GL_FLOAT, 2);
        layout.push(GL_FLOAT, 2);
        va.addBuffer(vb, layout);

        /* Index Buffer */
        IndexBuffer ib(indices, 6);

        /* Projection Matrix */
        glm::mat4 projection = glm::ortho(0.0f, 640.0f, 0.0f, 480.f, -100.0f, 100.0f);
        glm::mat4 view(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));


        /* Shaders */
        ProgramShader programShader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
        programShader.bind();

		Texture texture("resources/textures/flowersDrawing.png");
		texture.bind(0);
		programShader.setUniform1i("u_Texture", 0);

        va.unbind();
        vb.unbind();
        ib.unbind();
        programShader.unbind();

        Renderer renderer;

        /* ImGui settings e inicialización */
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330 core"); // GLSL Version
        ImGui::StyleColorsDark();
        

        float red = 0.0f;
        float incr = 0.05f;

        glm::vec3 translationA(0, 0, 0);
        glm::vec3 translationB(50, 0, 0);

        /* Render loop */
        while (!glfwWindowShouldClose(window))
        {
            renderer.clear();

            /* Inicialización ImGui */
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

            /* Draw */
            programShader.bind();

            // Voy a imprimir dos "objetos" cada uno con su mvp y comparten va y ib.
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
			glm::mat4 mvp = projection * view * model;
            programShader.setUniform4f("u_Color", red, 0.7f, 0.2f, 1.0f);
            programShader.setUniformMatrix4fv("u_MVP", mvp);
            renderer.draw(va, ib, programShader);

			model = glm::translate(glm::mat4(1.0f), translationB);
			mvp = projection * view * model;
			programShader.setUniform4f("u_Color", red, 0.7f, 0.2f, 1.0f); // No afecta pq en el shader usamos solo el color de la textura.
			programShader.setUniformMatrix4fv("u_MVP", mvp);
			renderer.draw(va, ib, programShader);

            // Actualmente no afecta por que el shader solo tiene en cuenta la textura.
            red += incr;
            if (red > 1.0f)
                incr = -0.05f;
            else if (red < 0.0f)
                incr = 0.05f;

            /* ImGui */

			{
                ImGui::Begin("Ajustes de objeto");
				//ImGui::Text("This is some useful text.");
				ImGui::SliderFloat3("TranslacionA", &translationA.x, 0.0f, 640.0f);
                ImGui::SliderFloat3("TranslacionB", &translationB.x, 0.0f, 640.0f);
				ImGui::Text("Media: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::End();
			}

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}