/**
 * @file IndexBuffer.cpp
 * @brief Implementación de la clase IndexBuffer.
 *
 * Clase de abstracción que facilita el uso de Index Buffers.
 *
 * @author Darío Rodríguez Hernández
 * @date 00/00/0000
 * @version 0.0
 */

#include "IndexBuffer.h"
#include "Renderer.h"
#include <iostream>
#include <GL/glew.h>

/**
* @brief Constructor de IndexBuffer.
*/
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint)); // Son siempre iguales, pero para prevenir que
                                                    // en alguna plaraforma no lo sea.

    m_Count = count;

    openGLCall(glGenBuffers(1, &m_IndexBufferID));
    openGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID));
    openGLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

/**
* @brief Destructor de IndexBuffer.
*/
IndexBuffer::~IndexBuffer() 
{
    openGLCall(glDeleteBuffers(1, &m_IndexBufferID));
}

/**
* @brief Selecciona (bind) IndexBuffer.
*/
void IndexBuffer::bind() const 
{
    openGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID));
}

/**
* @brief Deselecciona (bind(0)) IndexBuffer.
*/
void IndexBuffer::unbind() const
{
    openGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}