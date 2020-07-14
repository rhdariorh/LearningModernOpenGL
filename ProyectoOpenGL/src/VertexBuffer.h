/**
 * @file VertexBuffer.h
 * @brief Cabecera de la clase VertexBuffer.
 *
 * Clase de abstracción que facilita el uso de Vertex Buffers.
 *
 * @author Darío Rodríguez Hernández
 * @date 00/00/0000
 * @version 0.0
 */

#pragma once


/**
* @brief Clase de abstracción de Vertex Buffers.
* Clase de abstracción que facilita el uso de Vertex Buffers.
*/
class VertexBuffer
{
private:
	unsigned int m_VertexBufferID; ///< ID del Vertex Buffer.

public:
	/**
	* @brief Constructor de VertexBuffer.
	*/
	VertexBuffer(const void* data, unsigned int size);

	/**
	* @brief Constructor de VertexBuffer con indicio de dibujado.
	*/
	VertexBuffer(const void* data, unsigned int size, unsigned int drawHint);

	/**
	* @brief Destructor de VertexBuffer.
	*/
	~VertexBuffer();

	/**
	* @brief Selecciona (bind) el Vertex Buffer.
	*/
	void bind() const;

	/**
	* @brief Deselecciona el Vertex Buffer.
	*/
	void unbind() const;

	/**
	* @brief Asigna los datos al VertexBuffer.
	*/
	void setData(const void* data, unsigned int size);
};