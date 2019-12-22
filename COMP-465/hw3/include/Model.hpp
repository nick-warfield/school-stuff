#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// #define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../include/Shader.hpp"
#include "../include/Mesh.hpp"

class Model
{
	public:
		Model(const std::string&, bool = false);
		void draw(Shader);

	private:
		std::vector<Texture> m_texturesLoaded;
		std::vector<Mesh> m_meshes;
		std::string m_directory;
		bool m_gammaCorrection;

		void loadModel(const std::string&);
		void processNode(aiNode*, const aiScene*);
		Mesh processMesh(aiMesh*, const aiScene*);
		std::vector<Texture> loadMaterialTextures(aiMaterial*, aiTextureType, std::string);
};

#endif
