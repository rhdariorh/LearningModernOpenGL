/**
 * @file VertexBufferLayout.h
 * @brief Implementaci�n de la clase VertexBufferLayout.
 *
 * Clase de abstracci�n que facilita el uso del layout (distribuci�n)
 * para los Vertex Buffer. Adem�s se define un `struct` que contiene la
 * informaci�n que un elemento del buffer necesita.
 *
 * @author Dar�o Rodr�guez Hern�ndez
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
 * @brief A�ade un elemento al layout
 *
 * @param [in] type Tipo de dato (GL_FLOAT, GL_UNSIGNED_INT...).
 * @param [in] count N�mero (cantidad) de datos.
 */
void VertexBufferLayout::push(unsigned int type, unsigned int count)
{
	if(type == GL_UNSIGNED_BYTE)
		m_Elements.push_back({ type, count, GL_TRUE });
	else
		m_Elements.push_back({ type, count, GL_FALSE });

	m_Stride += VertexBufferElement::getSizeOfType(type) * count;
}