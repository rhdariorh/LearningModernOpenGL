#include "Shader.h"

Shader::Shader(const string& filepath)
{
	m_ShaderID = 0;
}

Shader::~Shader()
{
	compileShader();
}

bool Shader::compileShader()
{

}

void Shader::bind() const
{

}

void Shader::unbind() const
{

}

unsigned int Shader::getUniformLocation(const string& name)
{

}

void Shader::setUniform4f(const string& name, float v0, float v1, float v2, float v3)
{

}
