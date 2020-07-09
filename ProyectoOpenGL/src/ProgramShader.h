#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "GL/glew.h"
#include <unordered_map>
#include "glm/glm.hpp"

#include "DebugMacros.h"



class ProgramShader
{

private:
	unsigned int m_ProgramShaderID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	unsigned int getUniformLocation(const std::string &name);
	unsigned int createShaderProgram(const std::string &vertexShader, const std::string &fragmentShader);
	unsigned int compileShader(unsigned int type, const std::string &source);
	std::string fileToString(const std::string &filepath);

public:
	ProgramShader(const std::string &vertexFilepath, const std::string &fragmentFilepath);
	~ProgramShader();
	void bind() const;
	void unbind() const;

	/* Uniform setters */

	void setUniform1f(const std::string &name, float value);
	void setUniform2f(const std::string &name, float v0, float v1);
	void setUniform3f(const std::string &name, float v0, float v1, float v2);
	void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);

	 
	void setUniform1i(const std::string &name, int value);
	// void setUniform2i(const string &name, int v0, int v1);
	// void setUniform3i(const string &name, int v0, int v1, int v2);
	// void setUniform4i(const string &name, int v0, int v1, int v2, int v3);
	
	// void setUniform1ui(const string &name, unsigned int value);
	// void setUniform2ui(const string &name, unsigned int v0, unsigned int v1);
	// void setUniform3ui(const string &name, unsigned int v0, unsigned int v1, unsigned int v2);
	// void setUniform4ui(const string &name, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3);

	// void setUniform1fv(const string& name, unsigned int count, const float* value);
	// void setUniform2fv(const string& name, unsigned int count, const float* value);
	// void setUniform3fv(const string& name, unsigned int count, const float* value);
	// void setUniform4fv(const string& name, unsigned int count, const float* value);

	// void setUniform1iv(const string& name, unsigned int count, const int* value);
	// void setUniform2iv(const string& name, unsigned int count, const int* value);
	// void setUniform3iv(const string& name, unsigned int count, const int* value);
	// void setUniform4iv(const string& name, unsigned int count, const int* value);

	// void setUniform1uiv(const string& name, unsigned int count, const unsigned int* value);
	// void setUniform2uiv(const string& name, unsigned int count, const unsigned int* value);
	// void setUniform3uiv(const string& name, unsigned int count, const unsigned int* value);
	// void setUniform4uiv(const string& name, unsigned int count, const unsigned int* value);

	// void setUniformMatrix2fv(const string &name, unsigned int count, bool transpose, const float *value);
	// void setUniformMatrix3fv(const string &name, unsigned int count, bool transpose, const float* value);
	 void setUniformMatrix4fv(const std::string &name, const glm::mat4 &matrix);
	
	// void setUniformMatrix2x3fv(const string& name, unsigned int count, bool transpose, const float* value);
	// void setUniformMatrix3x2fv(const string& name, unsigned int count, bool transpose, const float* value);
	// void setUniformMatrix2x4fv(const string& name, unsigned int count, bool transpose, const float* value);
	// void setUniformMatrix4x2fv(const string& name, unsigned int count, bool transpose, const float* value);
	// void setUniformMatrix3x4fv(const string& name, unsigned int count, bool transpose, const float* value);
	// void setUniformMatrix4x3fv(const string& name, unsigned int count, bool transpose, const float* value);

};
