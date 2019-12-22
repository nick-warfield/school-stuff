#include "../include/Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (const std::ifstream::failure &e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
	}

	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	// create, compile, and check vertex shader
	uint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	compileCheck(vertexShader, "VERTEX");

	// create, compile, and check fragment shader
	uint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	compileCheck(fragmentShader, "FRAGMENT");

	// create, check, and link shader program
	m_shaderID = glCreateProgram();
	glAttachShader(m_shaderID, vertexShader);
	glAttachShader(m_shaderID, fragmentShader);
	glLinkProgram(m_shaderID);
	linkCheck(m_shaderID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

uint Shader::ID(void) const { return m_shaderID; }
void Shader::Use(void) const { glUseProgram(m_shaderID); }

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), (int)value);
}
void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), value);
}
void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), value);
}
void Shader::SetVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3i(glGetUniformLocation(m_shaderID, name.c_str()), x, y, z);
}
void Shader::SetVec3(const std::string& name, const glm::vec3& vec) const
{
	SetVec3(name, vec.x, vec.y, vec.z);
}
void Shader::SetMat4(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_shaderID, name.c_str()),
			1, GL_FALSE, glm::value_ptr(value));
}

void Shader::compileCheck(const uint& shader, const std::string& name) const
{
	int success;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::" << name
			<< "::COMPILATION::FAILED\n" << infoLog << std::endl;
	}
}
void Shader::linkCheck(const uint& shader) const
{
	int success;
	char infoLog[512];

	glGetShaderiv(shader, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINK::FAILED\n"
			<< infoLog << std::endl;
	}
}

