#include "Texture.h"
#include "stb_image/stb_image.h"

Texture::Texture(const std::string& path)
{
	m_TextureID = 0;
	m_FilePath = path;
	m_LocalBuffer = nullptr;
	m_Width = 0; m_Height = 0; m_BPP = 0;

	stbi_set_flip_vertically_on_load(1); // El inicio en OpenGL es abajo a la izquierda.

	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
	if (!m_LocalBuffer)
		std::cout << "[Texture Error](Texture <- Texture.cpp): error loading the texture file '" << path << "'." << std::endl;

	openGLCall(glGenTextures(1, &m_TextureID));
	openGLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

	openGLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	openGLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	openGLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	openGLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	openGLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	openGLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
	// Si quisiera conservar el buffer en la CPU, no haría el free anterior.
}

Texture::~Texture()
{
	openGLCall(glDeleteTextures(1, &m_TextureID)); // Para eliminar la textura de la GPU.
}

void Texture::bind(unsigned int slot) const
{
	//openGLCall(glBindTextureUnit(slot, m_TextureID)); Esta función hace lo mismo que las dos siguientes.
	openGLCall(glActiveTexture(GL_TEXTURE0 + slot));
	openGLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
}