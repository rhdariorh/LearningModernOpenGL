/**
 * @file Renderer.cpp
 * @brief Implementaci�n de la clase Renderer.
 *
 * A�adir descripci�n.
 *
 * @author Dar�o Rodr�guez Hern�ndez
 * @date 00/00/0000
 * @version 0.0
 */

#include "Renderer.h"
#include <iostream>
#include <GL/glew.h>



/**
 * Dibuja en pantalla con los par�metros introducidos.
 *
 * @param va Vertex Array
 * @param ib Index Buffer
 * @param programShader Shader
 */
void Renderer::draw(const VertexArray &va, const IndexBuffer &ib, const ProgramShader &programShader) const
{
	programShader.bind();
	va.bind();
	ib.bind();
    openGLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr)); // Null porque ya he asignado en glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

/**
 * @brief Limpia la pantalla (glClear()).
 */
void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}
