/**
 * @file main.cpp
 * @brief Proyecto base Modern OpenGL
 * Programa principal del proyecto base de Modern OpenGL.
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

#include "tests/Test.h"
#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"



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

    window = glfwCreateWindow(640, 480, "My window :)", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
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
        openGLCall(glEnable(GL_BLEND));
        openGLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


        Renderer renderer;

        /* ImGui settings */
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330 core"); // GLSL Version
        ImGui::StyleColorsDark();
        
        test::Test* currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu; // Se inicia en el menú.
        
        testMenu->registerTest<test::TestClearColor>("Clear Color"); // Lo registro para que se pueda crear cuando se pulse el botón.
        testMenu->registerTest<test::TestTexture2D>("Texture 2D");

        /* Render loop */
        while (!glfwWindowShouldClose(window))
        {
            renderer.clear();

            /* ImGui */
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

            if (currentTest)
            {
                currentTest->onUpdate(0.0f);
                currentTest->onRender();
                ImGui::Begin("Test options");
                if (currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->onImGuiRender();
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
		if (currentTest != testMenu)
			delete testMenu;

        delete currentTest;
    }

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}