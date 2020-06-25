/**
 * @file basic.vert
 * @brief Vertex shader
 *
 * @author Darío Rodríguez Hernández
 * @date 00/00/0000
 * @version 0.0
 */

//#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP; // Model View Projection Matrix

/*
* Main shader function
*/
void main()
{
   gl_Position = u_MVP * position;
   v_TexCoord = texCoord;
}