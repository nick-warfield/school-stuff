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
		Shader(const char*, const char*);

		uint ID(void) const;
		void Use(void) const;

		void SetBool(const std::string&, bool) const;
		void SetInt(const std::string&, int) const;
		void SetFloat(const std::string&, float) const;
		void SetVec3(const std::string&, float, float, float) const;
		void SetVec3(const std::string&, const glm::vec3&) const;
		void SetMat4(const std::string&, const glm::mat4&) const;

	private:
		uint m_shaderID;

		void compileCheck(const uint&, const std::string&) const;
		void linkCheck(const uint&) const;
};

#endif
