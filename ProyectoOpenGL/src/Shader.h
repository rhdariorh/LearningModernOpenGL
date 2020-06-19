#pragma once

#include <iostream>
#include <string>

using namespace std;

class Shader
{
private:
	unsigned int m_ShaderID;

	unsigned int getUniformLocation(const string& name);
	bool compileShader();
public:
	Shader(const string& filepath);
	~Shader();

	void bind() const;
	void unbind() const;

	void setUniform4f(const string& name, float v0, float v1, float v2, float v3);
};
