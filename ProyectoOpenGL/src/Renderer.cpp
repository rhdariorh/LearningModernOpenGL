/**
 * @file Renderer.cpp
 * @brief Implementación de la clase Renderer.
 *
 * Añadir descripción.
 *
 * @author Darío Rodríguez Hernández
 * @date 00/00/0000
 * @version 0.0
 */

#include "Renderer.h"
#include <iostream>
#include <GL/glew.h>

using namespace std;

/**
 * Limpia todos los flags de errores que ha producido OpenGL.
 */
void openGLClearError()
{
    while (glGetError());
}

/**
* Mira los errores (banderas) generados por OpenGL e imprime información de ellos.
*
* @param [in] function  Nombre de la función donde se está comprobando si hay errores.
* @param [in] line  Linea del código donde se encuentra la llamada a esa función.
* @retval true  No se ha encontrado ningun error
* @retval false Se ha encontrado un error
*/
bool openGLCheckError(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        cout << "[OpenGL Error]( " << function << " <- " << file << " <- Line: " << line << " ): " << error << endl;
        return false;
    }
    return true;
}