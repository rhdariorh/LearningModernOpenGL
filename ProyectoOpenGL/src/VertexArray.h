/**
 * @file VertexArray.h
 * @brief Cabecera de la clase VertexArray.
 * Clase que a�ade una capa de abstracci�n que facilita el uso de Vertex Arrays.
 *
 * @author Dar�o Rodr�guez Hern�ndez
 * @date 16/06/2020
 * @version 0.0
 */
#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

/**
* @brief Clase de abstracci�n que facilita el uso de Vertex Arrays.
*/
class VertexArray
{
private:
	unsigned int m_VertexArrayID;	///< ID del Vertex Array

public:
	/**
	* @brief Constructor de VertexArray
	*/
	VertexArray();
	/**
	* @brief Destructor de VertexArray
	*/
	~VertexArray();

	/**
	* @brief A�ade un Vertex Buffer y layout.
	*/
	void addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

	/**
	* @brief Selecciona (bind) el Vertex Array.
	*/
	void bind() const;

	/**
	* @brief Deselecciona (bind(0)) el Vertex Array.
	*/
	void unbind() const;
};