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

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Textures[2];

/*
* Main shader function
*/
void main()
{
	color = v_Color;

	int texIndex = int(v_TexIndex);
	color = texture(u_Textures[texIndex], v_TexCoord);
}