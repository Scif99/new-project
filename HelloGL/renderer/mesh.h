#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>

#include "buffer.h"
#include "shader.h"
#include "vertex.h"
#include "vertex_array.h"



#include <vector>

struct ModelTexture
{
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<ModelTexture> m_textures;

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;


public:
	~Mesh() = default;
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<ModelTexture>& textures);

	void Draw(const GLShader& shader);
};




#endif // !MESH_H

