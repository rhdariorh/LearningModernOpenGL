/**
 * @file VertexBuffer.cpp
 * @brief Implementación de la clase VertexBuffer.
 *
 * Clase de abstracción que facilita el uso de Vertex Buffers.
 *
 * @author Darío Rodríguez Hernández
 * @date 00/00/0000
 * @version 0.0
 */

#include "VertexBuffer.h"
#include "DebugMacros.h"
#include <iostream>
#include <GL/glew.h>


/**
* @brief Constructor de VertexBuffer.
*/
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    openGLCall(glGenBuffers(1, &m_VertexBufferID));
    openGLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID));
    openGLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

}

/**
* @brief Constructor de VertexBuffer con indicio de dibujado.
*/
VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int drawHint)
{
    openGLCall(glGenBuffers(1, &m_VertexBufferID));
    openGLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID));
    openGLCall(glBufferData(GL_ARRAY_BUFFER, size, data, drawHint));

}

/**
* @brief Destructor de VertexBuffer.
*/
VertexBuffer::~VertexBuffer() 
{
    openGLCall(glDeleteBuffers(1, &m_VertexBufferID));
}


/**
* @brief Selecciona (bind) el Vertex Buffer.
*/
void VertexBuffer::bind() const
{
    openGLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID));
}


/**
* @brief Deselecciona (bind(0)) el Vertex Buffer.
*/
void VertexBuffer::unbind() const
{
    openGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

/**
* @brief Asigna los datos al VertexBuffer.
*/
void VertexBuffer::setData(const void* data, unsigned int size) {
    openGLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}