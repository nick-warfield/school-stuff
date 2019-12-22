#ifndef MESH_HPP_INCLUDED
#define MESH_HPP_INCLUDED

#include <string>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../include/Shader.hpp"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 tangent;
	glm::vec3 bitTangent;
};

struct Texture
{
	uint id;
	std::string type;
	std::string path;
};

class Mesh
{
	public:
		Mesh(std::vector<Vertex>, std::vector<uint>, std::vector<Texture>);
		void draw(Shader);

	private:
		// probably need setters and getters
		std::vector<Vertex> m_verticies;
		std::vector<uint> m_indicies;
		std::vector<Texture> m_textures;
		uint m_VAO, m_VBO, m_EBO;

		static const int m_texture_diffuse;
		static const int m_texture_specular;
		static const int m_texture_normal;
		static const int m_texture_height;

		void setUpMesh(void);
};

#endif
