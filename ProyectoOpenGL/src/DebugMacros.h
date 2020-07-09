/**
 * @file DebugMacros.h
 * @brief Cabecera de las funciones de debug.
 *
 * Macros y funciones que ayudan a debugerar OpenGL.
 *
 * @author Dar�o Rodr�guez Hern�ndez
 * @date 00/00/0000
 * @version 0.0
 */

#pragma once

#include "GL/glew.h"
#include <iostream>


/**
* @def ASSERT(x)
* @brief A�ade un breakpoint si la condici�n es false.
*/
#define ASSERT(x) if (!(x)) __debugbreak();
/**
* @def openGLCall(x)
* @brief Crea un breakpoint en caso de error de OpenGL.
* Comprueba si se han creado errores en la funcion de OpenGL introducida y, en este caso, a�ade un breakpoint.
*/
#define openGLCall(x) openGLClearError(); x; ASSERT(openGLCheckError(#x, __FILE__, __LINE__));

/**
 * @brief Limpia errores que ha producido OpenGL.
 */
void openGLClearError();

/**
* @brief Imprime informaci�n si encuentra un error de OpenGL.
*/
bool openGLCheckError(const char* function, const char* file, int line);