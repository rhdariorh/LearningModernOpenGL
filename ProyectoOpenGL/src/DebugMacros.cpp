/**
 * @file DebugMacros.cpp
 * @brief Implementación de las funciones de debug.
 *
 * Macros y funciones que ayudan a debugerar OpenGL.
 *
 * @author Darío Rodríguez Hernández
 * @date 00/00/0000
 * @version 0.0
 */

#include "DebugMacros.h"

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
        std::cout << "[OpenGL Error]( " << function << " <- " << file << " <- Line: " << line << " ): " << error << std::endl;
        return false;
    }
    return true;
}