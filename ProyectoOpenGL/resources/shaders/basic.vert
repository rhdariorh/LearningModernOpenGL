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


/*
* Main shader function
*/
void main()
{
   gl_Position = position;
}