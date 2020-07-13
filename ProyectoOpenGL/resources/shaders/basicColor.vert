/**
 * @file basic.vert
 * @brief Vertex shader
 *
 * @author Dar�o Rodr�guez Hern�ndez
 * @date 00/00/0000
 * @version 0.0
 */

//#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float texIndex;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;

uniform mat4 u_MVP; // Model View Projection Matrix

/*
* Main shader function
*/
void main()
{
   gl_Position = u_MVP * position;
   v_Color = color;
   v_TexCoord = texCoord;
   v_TexIndex = texIndex;
}