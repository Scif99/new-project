#include "buffer.h"

//---------------------
//Vertex Buffer
//--------------------------
VertexBuffer::VertexBuffer(const float vertices[], unsigned int size)
{
	glGenBuffers(1, &m_renderer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_ID); //'How do we want to use this memory?'
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); //copy data into our buffer
}

//overload for meshes
VertexBuffer::VertexBuffer(const std::vector<float>& vertices)
{
	glGenBuffers(1, &m_renderer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_ID); //'How do we want to use this memory?'
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW); //copy data into our buffer
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_ID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


//------------------------
//INDEX BUFFER
//-----------------------

IndexBuffer::IndexBuffer(const unsigned int indices[], unsigned int size)
	:m_count{size/sizeof(unsigned int)}
{
	glGenBuffers(1, &m_renderer_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_ID); //'How do we want to use this memory?'
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW); //copy data into our buffer
}

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& indices)
	:m_count{ (unsigned int)indices.size()}
{
	glGenBuffers(1, &m_renderer_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_ID); //'How do we want to use this memory?'
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW); //copy data into our buffer
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_ID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
