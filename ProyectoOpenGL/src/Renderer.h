/**
 * @file Renderer.h
 * @brief Cabecera de la clase Renderer.
 *
 * Añadir descripción.
 *
 * @author Darío Rodríguez Hernández
 * @date 00/00/0000
 * @version 0.0
 */

#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ProgramShader.h"

class Renderer{
public:

	/**
	 * @brief Método de dibujado
	 */
	void draw(const VertexArray &va, const IndexBuffer &ib, const ProgramShader &programShader) const;

	/**
	 * @brief Limpia la pantalla (glClear()).
	 */
	void clear() const;
};