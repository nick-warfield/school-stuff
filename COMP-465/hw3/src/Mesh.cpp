#include "../include/Mesh.hpp"

constexpr uint stringToInt(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (stringToInt(str, h + 1) * 33) ^ str[h];
}

const int Mesh::m_texture_diffuse = stringToInt("texture_diffuse");
const int Mesh::m_texture_specular = stringToInt("texture_specular");
const int Mesh::m_texture_normal = stringToInt("texture_normal");
const int Mesh::m_texture_height = stringToInt("texture_height");

Mesh::Mesh(
		std::vector<Vertex> verticies,
		std::vector<uint> indicies,
		std::vector<Texture> textures) :
	m_verticies(verticies),
	m_indicies(indicies),
	m_textures(textures)
{
	setUpMesh();
}


void Mesh::draw(Shader shader)
{
	uint diffuseNr = 1;
	uint specularNr = 1;
	uint normalNr = 1;
	uint heightNr = 1;

	uint i = 0;
	for (auto& tex : m_textures)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		
		std::string number;
		switch (stringToInt(tex.type.c_str()))
		{
			case m_texture_diffuse: number = std::to_string(diffuseNr++); break;
			case m_texture_specular: number = std::to_string(specularNr++); break;
			case m_texture_normal: number = std::to_string(normalNr++); break;
			case m_texture_height: number = std::to_string(heightNr++); break;
		}

		glUniform1i(glGetUniformLocation(shader.ID(), (tex.type + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, tex.id);
		++i;
	}

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indicies.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void Mesh::setUpMesh(void)
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(
			GL_ARRAY_BUFFER,
			m_verticies.size() * sizeof(Vertex),
			&m_verticies[0],
			GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			m_indicies.size() * sizeof(uint),
			&m_indicies[0],
			GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
			2,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(void*)offsetof(Vertex, texCoords));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(
			3,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(void*)offsetof(Vertex, tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(
			4,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(void*)offsetof(Vertex, bitTangent));

	glBindVertexArray(0);
}

