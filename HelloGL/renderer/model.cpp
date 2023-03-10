#pragma once
#include "model.h"

unsigned int TextureFromFile(const char* path, const std::string& directory);

Model::Model(const std::string& path)
{
	//1) use Assimp to load model from external format into a scene object
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs); //TODO - post-processing options?
	//handle any errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	m_directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);

}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	//process meshes in current node
	for (int i = 0; i < node->mNumMeshes;++i)
	{
		//get corresponding scene mesh
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		//
		m_meshes.push_back(processMesh(mesh, scene));
	}

	//recursively process child nodes
	for (int i = 0;i < node->mNumChildren;++i)
	{
		processNode(node->mChildren[i], scene);
	}
}


//translate the aiMesh into a Mesh object that can be used within this application
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<ModelTexture> textures;

	//process vertices
	for (int i = 0; i < mesh->mNumVertices;++i)
	{
		Vertex vertex;
		//process positions
		glm::vec3 vector; //use a temp vec3 to convert from assimp's data types
		vector = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
		vertex.m_position = vector;
		//process normals
		vector = { mesh->mNormals[i].x ,  mesh->mNormals[i].y,  mesh->mNormals[i].z };
		vertex.m_normal = vector;
		//process texture coords
		//Note, model might not contain texture coords, so first check if they exist
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.m_tex_coords = vec;
			/*
				// tangent
				vector.x = mesh->mTangents[i].x;
				vector.y = mesh->mTangents[i].y;
				vector.z = mesh->mTangents[i].z;
				vertex.Tangent = vector;
				// bitangent
				vector.x = mesh->mBitangents[i].x;
				vector.y = mesh->mBitangents[i].y;
				vector.z = mesh->mBitangents[i].z;
				vertex.Bitangent = vector;
				*/
		}
		else
			vertex.m_tex_coords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	//process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	//process materials
	if (mesh->mMaterialIndex >= 0) //mesh might not have a materisl
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<ModelTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<ModelTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	}
	return Mesh(vertices, indices, textures);
}

std::vector<ModelTexture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<ModelTexture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip{ false };
		//optimisation : check if we have already loaded this texture
		for (unsigned int j = 0; j < m_textures_loaded.size();++j)
		{
			if (std::strcmp(str.C_Str(), m_textures_loaded[j].path.data()) == 0)
			{
				textures.push_back(m_textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			ModelTexture texture;
			texture.id = TextureFromFile(str.C_Str(), m_directory);
			texture.type = typeName;
			textures.push_back(texture);
		}

	}
	return textures;
}

unsigned int TextureFromFile(const char* path, const std::string& directory)
{
	//get path relative to project root
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
void Model::Draw(GLShader& shader)
{
	for (auto& mesh : m_meshes)
	{
		mesh.Draw(shader);
	}
}