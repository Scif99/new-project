#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <algorithm>
#include <iostream>
#include <vector>

#include "mesh.h"
#include "shader.h"
#include "stb_image.h"

class Model
{
private:
	std::vector<Mesh> m_meshes;
	std::string m_directory;
	std::vector<ModelTexture> m_textures_loaded; //stores textures as we load them, so that we can reuse.

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh , const aiScene* scene);
	std::vector<ModelTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);


public:
	Model(const std::string& path);
	~Model() = default;
	void Draw(GLShader& shader);

};




#endif // !MODEL_H
