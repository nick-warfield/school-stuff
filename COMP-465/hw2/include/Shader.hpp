#ifndef SHADER_LOADER_HPP_INCLUDED
#define SHADER_LOADER_HPP_INCLUDED

#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
	public:
		Shader(const char* vertexPath, const char* fragmentPath)
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

		uint ID(void) { return m_shaderID; }
		void Use(void) { glUseProgram(m_shaderID); }

		void SetBool(const std::string& name, bool value) const
		{
			glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), (int)value);
		}
		void SetInt(const std::string& name, int value) const
		{
			glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), value);
		}
		void SetFloat(const std::string& name, float value) const
		{
			glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), value);
		}
		void SetMat4(const std::string& name, glm::mat4 value)
		{
			glUniformMatrix4fv(glGetUniformLocation(m_shaderID, name.c_str()),
					1, GL_FALSE, glm::value_ptr(value));
		}

	private:
		uint m_shaderID;

		void compileCheck(uint shader, const std::string& name)
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
		void linkCheck(uint shader)
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

};

#endif
