/**
 * @file VertexArray.cpp
 * @brief Implementación de la clase VertexArray.
 * Clase que añade una capa de abstracción que facilita el uso de Vertex Arrays.
 *
 * @author Darío Rodríguez Hernández
 * @date 16/06/2020
 * @version 0.0
 */

#include "VertexArray.h"
#include "Renderer.h"

/**
* @brief Constructor de VertexArray
*/
VertexArray::VertexArray()
{
	openGLCall(glGenVertexArrays(1, &m_VertexArrayID));
}

/**
* @brief Destructor de VertexArray
*/
VertexArray::~VertexArray()
{

}

/**
* @brief Añade un Vertex Buffer y layout.
* Añade un Vertex Buffer con su respectivo VertexBufferLayout.
*/
void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	bind();
	vb.bind();
	const vector<VertexBufferElement>& elements = layout.getElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const VertexBufferElement& element = elements[i];
		openGLCall(glEnableVertexAttribArray(i));
		// Causa un warning al convertir unsigned int (4 bytes) a const void* (8 bytes). No es un problema.
		openGLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
}

/**
* @brief Selecciona (bind) el Vertex Array.
*/
void VertexArray::bind() const
{
	openGLCall(glBindVertexArray(m_VertexArrayID));
}

/**
* @brief Deselecciona (bind(0)) el Vertex Array.
*/
void VertexArray::unbind() const
{
	openGLCall(glBindVertexArray(0));
}