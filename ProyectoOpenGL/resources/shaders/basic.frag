/**
 * @file basic.frag
 * @brief Fragment shader
 *
 * @author Darío Rodríguez Hernández
 * @date 00/00/0000
 * @version 0.0
 */

//#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

/*
* Main shader function
*/
void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;
}