/**
 * @file VertexBufferLayout.h
 * @brief Implementación de la clase VertexBufferLayout.
 *
 * Clase de abstracción que facilita el uso del layout (distribución)
 * para los Vertex Buffer. Además se define un `struct` que contiene la
 * información que un elemento del buffer necesita.
 *
 * @author Darío Rodríguez Hernández
 * @date 16/06/2020
 * @version 0.0
 */

#include "VertexBufferLayout.h"

/**
* @brief Constructor de VertexBufferLayout
*/
VertexBufferLayout::VertexBufferLayout()
{
	m_Stride = 0;
}

/**
 * @brief Añade un elemento al layout
 *
 * @param [in] type Tipo de dato (GL_FLOAT, GL_UNSIGNED_INT...).
 * @param [in] count Número (cantidad) de datos.
 */
void VertexBufferLayout::push(unsigned int type, unsigned int count)
{
	if(type == GL_UNSIGNED_BYTE)
		m_Elements.push_back({ type, count, GL_TRUE });
	else
		m_Elements.push_back({ type, count, GL_FALSE });

	m_Stride += VertexBufferElement::getSizeOfType(type) * count;
}