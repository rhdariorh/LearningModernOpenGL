/**
 * @file main.cpp
 * @brief Proyecto base OpenGL
 *
 * @author Darío Rodríguez
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
using namespace std;

/**
* @def ASSERT(x)
* @brief Si x es FALSE, añade un breakpoint en la linea donde se ha producido.
*/
#define ASSERT(x) if (!(x)) __debugbreak();
/**
* @def openGLCall(x)
* @brief Comprueba si se han creado errores en la funcion de OpenGL introducida y, en este caso, añade un breakpoint.
*/
#define openGLCall(x) openGLClearError(); x; ASSERT(openGLCheckError(#x, __FILE__, __LINE__));

/**
 * @brief Limpia todos los flags de errores que ha producido OpenGL.
 */
static void openGLClearError()
{
    while (glGetError());
}

/**
* @brief Mira los errores (banderas) generados por OpenGL e imprime información de ellos.
*
* @param [in] function Nombre de la función donde se está comprobando si hay errores.
* @param [in] line Linea del código donde se encuentra la llamada a esa función.
* @return No se encuentran errores
*/
static bool openGLCheckError(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError()) 
    {
        cout << "[OpenGL Error]( " << function << " <- " << file << " <- Line: " << line << " ): " << error << endl;
        return false;
    }
    return true;
}

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
* Main function
*/
int main(void)
{
    GLFWwindow* window;

    /* Initialize GLFW */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "My window :)", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    /* Initialize GLEW */
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "[GLEW Error]: %s\n", glewGetErrorString(err));
    }

    // Print initial info
    cout << "Versions:\n";
    cout << "---OpenGL:\t" << glGetString(GL_VERSION) << "\n";
    cout << "---GLSL:\t" << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
    cout << "---GLFW:\t" << glfwGetVersionString() << "\n";
    cout << "---GLEW:\t" << glewGetString(GLEW_VERSION) << "\n";


    /* Geometries */
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

    // RECORDAR QUE OPENGL ES UNA MAQUINA DE ESTADOS //

    // Se crea un Vertex Array y se selecciona (bind).
    unsigned int vao; // Vertex array object
    openGLCall(glGenVertexArrays(1, &vao));
    openGLCall(glBindVertexArray(vao));

    // Se crea un Vertex Buffer y se selecciona (bind).
    unsigned int buffer; // Vertex buffer object
    openGLCall(glGenBuffers(1, &buffer));
    openGLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    openGLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW));
    
    // Después se elige el layout que se va a usar para interpretar el buffer 0. Esto ligará el
    // vertex buffer con el vertex array. 
    openGLCall(glEnableVertexAttribArray(0));
    openGLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0)); // Esto relaciona el buffer con el vao


    unsigned int ibo; // Index buffer object
    openGLCall(glGenBuffers(1, &ibo));
    openGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    openGLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

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

        openGLCall(glBindVertexArray(vao));
        openGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo)); // To-Do: Mirar si los ibo también se almacenan en el vao. Si es así, no hace falta esta linea.

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

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}