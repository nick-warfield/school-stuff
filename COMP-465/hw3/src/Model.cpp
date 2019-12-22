#include "../include/Model.hpp"

uint LoadTextureFromFile(
		const char *path,
		const std::string& directory,
		bool gamma = false)
{
	std::string fileName(directory + '/' + path);
	uint textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(
			fileName.c_str(),
			&width,
			&height,
			&nrComponents,
			0);

	if (data)
	{
		GLenum format;
		switch (nrComponents)
		{
			case 1: format = GL_RED; break;
			case 3: format = GL_RGB; break;
			case 4: format = GL_RGBA; break;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(
				GL_TEXTURE_2D,
				0,
				format,
				width,
				height,
				0,
				format,
				GL_UNSIGNED_BYTE,
				data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cerr << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

Model::Model(const std::string& path, bool gamma) :
	m_gammaCorrection(gamma)
{
	loadModel(path);
}

void Model::draw(Shader shader)
{
	for (auto& mesh : m_meshes) { mesh.draw(shader); }
}

void Model::loadModel(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(
			path,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	m_directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
	// process all of the meshes on this node
	for (uint i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, scene));
	}

	// process children
	for (uint i = 0; i < node->mNumChildren; ++i)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
	std::vector<Vertex> verticies;
	std::vector<uint> indicies;
	std::vector<Texture> textures;

	// load vertex
	for (uint i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vert;
		vert.position = glm::vec3(
				mesh->mVertices[i].x,
				mesh->mVertices[i].y,
				mesh->mVertices[i].z);

		vert.normal = glm::vec3(
				mesh->mNormals[i].x,
				mesh->mNormals[i].y,
				mesh->mNormals[i].z);

		if (mesh->mTextureCoords[0])
		{
			vert.texCoords = glm::vec2(
					mesh->mTextureCoords[0][i].x,
					mesh->mTextureCoords[0][i].y);
		}
		else
		{
			vert.texCoords = glm::vec2(0, 0);
		}

		vert.tangent = glm::vec3(
				mesh->mTangents[i].x,
				mesh->mTangents[i].y,
				mesh->mTangents[i].z);

		vert.bitTangent = glm::vec3(
				mesh->mBitangents[i].x,
				mesh->mBitangents[i].y,
				mesh->mBitangents[i].z);

		verticies.push_back(vert);
	}

	// load indicies
	for (uint i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (uint j = 0; j < face.mNumIndices; ++j)
		{
			indicies.push_back(face.mIndices[j]);
		}
	}

	// process material
	aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
	std::vector<Texture> diffuseMaps = loadMaterialTextures(
			material,
			aiTextureType_DIFFUSE,
			"texture_diffuse");
	std::vector<Texture> speculareMaps = loadMaterialTextures(
			material,
			aiTextureType_DIFFUSE,
			"texture_specular");
	std::vector<Texture> normalMaps = loadMaterialTextures(
			material,
			aiTextureType_DIFFUSE,
			"texture_normal");
	std::vector<Texture> heightMaps = loadMaterialTextures(
			material,
			aiTextureType_DIFFUSE,
			"texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	return Mesh(verticies, indicies, textures);
}

std::vector<Texture> Model::loadMaterialTextures(
		aiMaterial *material, 
		aiTextureType type,
		std::string typeName)
{
	std::vector<Texture> textures;
	for (uint i = 0; i < material->GetTextureCount(type); ++i)
	{
		aiString str;
		material->GetTexture(type, i, &str);
		bool loaded = false;
		for (uint j = 0; j < m_texturesLoaded.size(); ++j)
		{
			if (std::strcmp(m_texturesLoaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(m_texturesLoaded[j]);
				loaded = true;
				break;
			}
		}

		if (!loaded)
		{
			Texture tex;
			tex.id = LoadTextureFromFile(str.C_Str(), m_directory);
			tex.type = typeName;
			tex.path = str.C_Str();
			textures.push_back(tex);
			m_texturesLoaded.push_back(tex);
		}
	}

	return textures;
}

