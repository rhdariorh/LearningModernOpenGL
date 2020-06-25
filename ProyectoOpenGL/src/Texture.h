#pragma once

#include "DebugMacros.h"

class Texture
{
private:
	unsigned int m_TextureID;
	string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const string& path);
	~Texture();

	void bind(unsigned int slot = 0) const ;
	void unbind() const;

	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }
	inline int getBPP() const { return m_BPP; }
};
