/**
 * @file DebugMacros.cpp
 * @brief Implementaci�n de las funciones de debug.
 *
 * Macros y funciones que ayudan a debugerar OpenGL.
 *
 * @author Dar�o Rodr�guez Hern�ndez
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
* Mira los errores (banderas) generados por OpenGL e imprime informaci�n de ellos.
*
* @param [in] function  Nombre de la funci�n donde se est� comprobando si hay errores.
* @param [in] line  Linea del c�digo donde se encuentra la llamada a esa funci�n.
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