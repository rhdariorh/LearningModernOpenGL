/**
 * @file basic.frag
 * @brief Fragment shader
 *
 * @author Darío Rodríguez
 * @date 00/00/0000
 * @version 0.0
 */

//#shader fragment
//#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

/*
* Main shader function
*/
void main()
{
   color = u_Color;
}