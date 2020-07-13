#include "ProgramShader.h"

ProgramShader::ProgramShader(const std::string &vertexFilepath, const std::string &fragmentFilepath)
{
    m_ProgramShaderID = 0;
    
    std::string vertexShader = fileToString(vertexFilepath);
	std::string fragmentShader = fileToString(fragmentFilepath);
    
    m_ProgramShaderID = createShaderProgram(vertexShader, fragmentShader);
}

ProgramShader::~ProgramShader()
{
    openGLCall(glDeleteProgram(m_ProgramShaderID));
}

void ProgramShader::bind() const
{
    openGLCall(glUseProgram(m_ProgramShaderID));
}

void ProgramShader::unbind() const
{
    openGLCall(glUseProgram(0));
}

unsigned int ProgramShader::getUniformLocation(const std::string &name)
{
    int location;
    if (m_UniformLocationCache.find(name) == m_UniformLocationCache.end()) // Para tener que buscarlo solo 1 vez con glGetUniformLocation().
    {
		openGLCall(location = glGetUniformLocation(m_ProgramShaderID, name.c_str()));
		if (location == -1) // -1: Can't find that uniform
			std::cout << "[Shader Warning](getUniformLocation <- ProgramShader.cpp): Uniform " << name << " is not used or declared." << std::endl;
        m_UniformLocationCache[name] = location;
    }
    else
    {
        location = m_UniformLocationCache[name];
    }
    
    return location;
}

/**
 * @brief Crea el programa con los shaders introducidos.
 *
 * @param [in] vertexShader Código del vertex shader.
 * @param [in] fragmentShader Código del fragment shader.
 * @return ID del programa creado.
 */
unsigned int ProgramShader::createShaderProgram(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

/**
 * @brief Crea y compila un shader del tipo y código introducido.
 *
 * @param [in] type tipo de shader
 * @param [in] source código del shader a crear.
 * @return ID del shader creado.
 */
unsigned int ProgramShader::compileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (!result) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char)); // No se puede "char* message[length]" porque length no tiene un valor asignado inicialmente.
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl; // Suponemos que solo usamos esos 2 tipos de shaders.
        std::cout << message << std::endl;

        glDeleteShader(id);

        return 0;
    }
    return id;
}

/**
 * @brief Introduce en un std::string el contenido de un fichero.
 *
 * @param [in] filepath ruta del fichero
 * @return Cadena de caracteres con el contenido del fichero.
 */
std::string ProgramShader::fileToString(const std::string &filepath) 
{

    std::string source = "";
    std:: ifstream stream(filepath);
    if (stream.is_open()) {
        std::string line;
        std::stringstream ss;
        while (getline(stream, line))
        {
            ss << line << '\n';
        }
        source = ss.str();
    }
    else
    {
        std::cout << "[Stream Error] (fileTostd::string() <- ProgramShader.cpp): Stream is not open." << std::endl;
    }

    return source;
}

/* Uniform setters */

void ProgramShader::setUniform1f(const std::string &name, float value)
{
	unsigned int location = ProgramShader::getUniformLocation(name);
	openGLCall(glUniform1f(location, value));
}

void ProgramShader::setUniform2f(const std::string &name, float v0, float v1)
{
	unsigned int location = ProgramShader::getUniformLocation(name);
	openGLCall(glUniform2f(location, v0, v1));
}

void ProgramShader::setUniform3f(const std::string &name, float v0, float v1, float v2)
{
	unsigned int location = ProgramShader::getUniformLocation(name);
	openGLCall(glUniform3f(location, v0, v1, v2));
}

void ProgramShader::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
{
	unsigned int location = ProgramShader::getUniformLocation(name);
	openGLCall(glUniform4f(location, v0, v1, v2, v3));
}

void ProgramShader::setUniform1i(const std::string& name, int value)
{
	unsigned int location = ProgramShader::getUniformLocation(name);
	openGLCall(glUniform1i(location, value));
}

void ProgramShader::setUniform1iv(const std::string& name, unsigned int count, const int* value)
{
    unsigned int location = ProgramShader::getUniformLocation(name);
    openGLCall(glUniform1iv(location, count, value));
}

void ProgramShader::setUniformMatrix4fv(const std::string& name, const glm::mat4& matrix)
{
    unsigned int location = ProgramShader::getUniformLocation(name);
    openGLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
}

