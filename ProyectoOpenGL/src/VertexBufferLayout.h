/**
 * @file VertexBufferLayout.h
 * @brief Cabecera de la clase VertexBufferLayout.
 *
 * Clase de abstracción que facilita el uso del layout (distribución)
 * para los Vertex Buffer. Además se define un `struct` que contiene la
 * información que un elemento del buffer necesita.
 *
 * @author Darío Rodríguez Hernández
 * @date 16/06/2020
 * @version 0.0
 */
#pragma once

#include <iostream>
#include <vector>
#include <GL/glew.h>

using namespace std;

/**
* Elementos del layout del Vertex Buffer.  
*/
struct VertexBufferElement
{
	unsigned int type;			///< Tipo de dato
	unsigned int count;			///< Número de componentes por vértice
	unsigned int normalized;	///< Normalizar o no valores

	/**
	* @brief Devuelve el tamaño de un tipo de dato
	* Devuelve el tamaño en bytes de un tipo de dato GL_FLOAT,
	* GL_UNSIGNED_INT o GL_UNSIGNED_BYTE.
	*/
	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return sizeof(float);
			case GL_UNSIGNED_INT:	return sizeof(unsigned int);
			case GL_UNSIGNED_BYTE:	return 1;
		}
		return 0;
	}
};

/**
* @brief Abstracción para el uso cómodo de layouts de Vertex Buffers.
*
* Clase de abstracción que facilita el uso del layout (distribución) 
* para los Vertex Buffer. Almacena los elementos de los diferentes 
* atributos que hay en el Vertex Buffer.
*/

class VertexBufferLayout
{
private:
	vector<VertexBufferElement> m_Elements;	///< Elementos del layout.
	unsigned int m_Stride;					///< Tamaño o paso del Layout completo.

public:
	/**
	* @brief Constructor de VertexBufferLayout
	*/
	VertexBufferLayout();

	/**
	* @brief Devuelve el tamaño o paso del layout completo.
	*/
	inline unsigned int getStride() const { return m_Stride; }

	/**
	* @brief Devuelve los elementos del layout.
	* @return Elementos del layout.
	*/
	inline const vector<VertexBufferElement> getElements() const { return m_Elements; }

	/**
	 * @brief Añade un elemento al layout
	 * 
	 * @param [in] type Tipo de dato (GL_FLOAT, GL_UNSIGNED_INT...).
	 * @param [in] count Número (cantidad) de datos.
	 */
	void push(unsigned int type, unsigned int count);

	/*
	* Ejemplo de como hacer push con plantillas:

	template<typename T>
	void push(unsigned int count)
	{
		cout << "[C++ Error](push() <- VertexBufferLayout.cpp): You must to specify the type to push (push<type>(count))." << endl;
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
	}
		*/
};