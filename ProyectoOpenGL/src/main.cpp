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
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Mis clases
#include "DebugMacros.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ProgramShader.h"
#include "Texture.h"

using namespace std;

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
    cout << "Versions:\n";
    cout << "---OpenGL:\t" << glGetString(GL_VERSION) << endl;
    cout << "---GLSL:\t" << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cout << "---GLFW:\t" << glfwGetVersionString() << endl;
    cout << "---GLEW:\t" << glewGetString(GLEW_VERSION) << endl << endl;
    //////////////////////////////////////////////////////////////////////////////////////

    /*******************/
    /* PARTE PRINCIPAL */
    /*******************/

    {
        /* Geometrias */
        float positions[16] = {
            -0.5f, -0.5f, 0.0f, 0.0f, // 0 | pos, tex
             0.5f, -0.5f, 1.0f, 0.0f, // 1 | pos, tex
             0.5f,  0.5f, 1.0f, 1.0f, // 2 | pos, tex
            -0.5f,  0.5f, 0.0f, 1.0f  // 3 | pos, tex
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
        glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
        glm::mat4 view(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(1, 1, 0));

        glm::mat4 mvp = projection * view * model;

        /* Shaders */
        ProgramShader programShader("resources/shaders/basic.vert", "resources/shaders/basic.frag");
        programShader.bind();
        programShader.setUniformMatrix4fv("u_MVP", mvp);

		Texture texture("resources/textures/flowersDrawing.png");
		texture.bind(0);
		programShader.setUniform1i("u_Texture", 0);

        va.unbind();
        vb.unbind();
        ib.unbind();
        programShader.unbind();

        Renderer renderer;

        float red = 0.0f;
        float incr = 0.05f;

        /* Render loop */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.clear();

            /* Draw */
            programShader.bind();
            programShader.setUniform4f("u_Color", red, 0.7f, 0.2f, 1.0f);

            renderer.draw(va, ib, programShader);

            red += incr;
            if (red > 1.0f)
                incr = -0.05f;
            else if (red < 0.0f)
                incr = 0.05f;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}