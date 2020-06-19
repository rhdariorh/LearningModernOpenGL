/**
 * @file IndexBuffer.h
 * @brief Cabecera de la clase IndexBuffer.
 *
 * Clase de abstracci�n que facilita el uso de Index Buffers.
 *
 * @author Dar�o Rodr�guez Hern�ndez
 * @date 00/00/0000
 * @version 0.0
 */

#pragma once

/**
* @brief Clase de abstracci�n que facilita el uso de Index Buffers.
*/
class IndexBuffer
{
private:
	unsigned int m_IndexBufferID;	///< ID del Index Buffer.
	unsigned int m_Count;			///< N�mero (cantidad) de datos.
public:

	/**
	* @brief Constructor de IndexBuffer.
	*/
	IndexBuffer(const unsigned int* data, unsigned int count);
	
	/**
	* @brief Destructor de IndexBuffer.
	*/
	~IndexBuffer();

	/**
	* @brief Selecciona (bind) IndexBuffer.
	*/
	void bind() const;

	/**
	* @brief Deselecciona (bind(0)) IndexBuffer.
	*/
	void unbind() const;

	/**
	* @brief Devuelve el n�mero de datos del Index Buffer.
	* @return Count. N�mero (cantidad) de datos del Index Buffer.
	*/
	inline unsigned int getCount() const { return m_Count; }
};