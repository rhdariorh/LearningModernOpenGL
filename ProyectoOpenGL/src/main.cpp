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

// Mis clases
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

using namespace std;


/**
 * @brief Introduce en un string el contenido de un fichero.
 *
 * @param [in] filepath ruta del fichero
 * @return Cadena de caracteres con el contenido del fichero.
 */
static string fileToString(const string& filepath) {

    string source = "";
    ifstream stream(filepath);
    if (stream.is_open()) {
        string line;
        stringstream ss;
        while (getline(stream, line))
        {
            ss << line << '\n';
        }
        source = ss.str();
    }
    else
    {
        cout << "[Stream Error] (fileToString() <- main.cpp): Stream is not open." << endl;
    }

    return source;
}

/**
 * @brief Crea y compila un shader del tipo y código introducido.
 *
 * @param [in] type tipo de shader
 * @param [in] source código del shader a crear.
 * @return ID del shader creado.
 */
static unsigned int compileShader(unsigned int type, const string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (!result) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char)); // No se puede "char* message[length]" porque length no tiene un valor asignado inicialmente.
        glGetShaderInfoLog(id, length, &length, message);
        cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << endl; // Suponemos que solo usamos esos 2 tipos de shaders.
        cout << message << endl;

        glDeleteShader(id);

        return 0;
    }
    return id;
}

/**
 * @brief Crea el programa con los shaders introducidos.
 *
 * @param [in] vertexShader Código del vertex shader.
 * @param [in] fragmentShader Código del fragment shader.
 * @return ID del programa creado.
 */
static unsigned int createShaderProgram(const string& vertexShader, const string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

/*
* Función principal
*/
int main(void)
{
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
    cout << "---OpenGL:\t" << glGetString(GL_VERSION) << "\n";
    cout << "---GLSL:\t" << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
    cout << "---GLFW:\t" << glfwGetVersionString() << "\n";
    cout << "---GLEW:\t" << glewGetString(GLEW_VERSION) << "\n";


    /*******************/
    /* PARTE PRINCIPAL */
    /*******************/
    {
        /* Geometrias */
        float positions[8] = {
            -0.5f, -0.5f, // 0
             0.5f, -0.5f, // 1
             0.5f,  0.5f, // 2
            -0.5f,  0.5f  // 3
        };

        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        unsigned int vao; // Vertex array object
        openGLCall(glGenVertexArrays(1, &vao));
        openGLCall(glBindVertexArray(vao));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        VertexBufferLayout layout;
        layout.push<float>(2);
        va.addBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        /* Shaders */
        string vertexShader = fileToString("resources/shaders/basic.vert");
        string fragmentShader = fileToString("resources/shaders/basic.frag");

        unsigned int shader = createShaderProgram(vertexShader, fragmentShader);
        openGLCall(int location = glGetUniformLocation(shader, "u_Color"));
        ASSERT(location != -1); // -1: Can't find that uniform

        float red = 0.0f;
        float incr = 0.05f;
        /* Render loop */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Draw */
            glUseProgram(shader);
            openGLCall(glUniform4f(location, red, 0.7f, 0.2f, 1.0f));

            //openGLCall(glBindVertexArray(vao));
            vb.bind(); // To-Do: Mirar si los ibo también se almacenan en el vao. Si es así, no hace falta esta linea.
            ib.bind();

            openGLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));  // Null porque ya he asignado en glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

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

        openGLCall(glDeleteProgram(shader));
    }

    glfwTerminate();
    return 0;
}