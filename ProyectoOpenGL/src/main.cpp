/**
 * @file main.cpp
 * @brief Proyecto base Modern OpenGL
 * Programa principal del proyecto base de Modern OpenGL.
 *
 * @author Dar�o Rodr�guez Hern�ndez
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
#include <math.h> 
#include <chrono>
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

#include "Test.h"
#include "TestClearColor.h"
#include "TestTexture2D.h"
#include "batch/TestBatchRendering.h"
#include "batch/TestBatchRenderDynamicGeo.h"

#define PI 3.14159265

/*
* Funci�n principal
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

    // Imprimir informaci�n inicial
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
        currentTest = testMenu; // Se inicia en el men�.
        
        testMenu->registerTest<test::TestClearColor>("Clear Color"); // Lo registro para que se pueda crear cuando se pulse el bot�n.
        testMenu->registerTest<test::TestTexture2D>("Texture 2D");
        testMenu->registerTest<test::TestBatchRendering>("Batch Rendering - Textures");
        testMenu->registerTest<test::TestBatchRenderDynamicGeo>("Batch Rendering - Dynamic Geometry");

        float angle = 0;
        /* Render loop */
        while (!glfwWindowShouldClose(window))
        {
            if (angle == 360)
                angle = 1;
            else
                angle++;

            renderer.clear();

            /* ImGui */
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

            if (currentTest)
            {
                currentTest->onUpdate((sin(angle * PI / 180) + 1)/2);
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