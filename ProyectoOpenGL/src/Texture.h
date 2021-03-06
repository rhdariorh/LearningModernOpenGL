#pragma once

#include "DebugMacros.h"

class Texture
{
private:
	unsigned int m_TextureID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& path);
	~Texture();

	void bind(unsigned int slot = 0) const ;
	static inline void unbind() { openGLCall(glBindTexture(GL_TEXTURE_2D, 0)) }

	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }
	inline int getBPP() const { return m_BPP; }
};
