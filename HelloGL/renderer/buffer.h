#ifndef BUFFER_H
#define BUFFER_H


#include <glad/glad.h>
#include <vector>

#include <string>

#include "vertex.h"

/*An API-agnostic data type for buffer elements*/
static enum class ShaderDataType
{
	None = 0, Float, Float2, Float3, Float4
};

static unsigned int ShaderDataTypeSize(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Float: return 4;
		case ShaderDataType::Float2: return 2*4;
		case ShaderDataType::Float3: return 3*4;
		case ShaderDataType::Float4: return 4*4;
	}
	assert(true && "UNKNOWN SHADER DATA TYPE");
	return 0;
}


/*
A BufferElement is essentially a vertex attribute
- For example, position, texture coordinates etc...
*/
struct BufferElement
{
	//std::string m_name;
	ShaderDataType m_type{ShaderDataType::None};
	unsigned int m_size;
	unsigned int m_offset;

	BufferElement() = default;

	BufferElement(ShaderDataType type)//, const std::string& name)
		: /*m_name{name},*/ m_type{type}, m_size{ShaderDataTypeSize(type)}, m_offset{0}
	{}

	unsigned int GetcomponentCount() const
	{
		switch (m_type)
		{
			case ShaderDataType::Float:  return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
		}
	}
};

/*
* A BufferLayout is a container for BufferElements that stores information such as the stride and offset
* We can't just use a vector of BufferElements because, in order to know the stride, and the offset of an attribute,
* we need to know about other elements
*/
class BufferLayout
{
public:
	std::vector<BufferElement> m_elements;
	unsigned int m_stride{ 0 };

	BufferLayout() = default;

	BufferLayout(const std::vector<BufferElement>& elements)
		:m_elements{ elements } 
	{
		CalculateOffsetsAndStride();
	}

	auto begin() const { return m_elements.begin(); }
	auto begin() { return m_elements.begin(); }

	auto end() const { return m_elements.end(); }
	auto end() { return m_elements.end(); }


private:
	void CalculateOffsetsAndStride()
	{
		m_stride = 0;
		for (auto& e : m_elements)
		{
			e.m_offset = m_stride;
			m_stride += e.m_size;
		}
	}
};


class VertexBuffer
{
private:
	unsigned int m_renderer_ID;
	BufferLayout m_layout;
public:
	~VertexBuffer() { glDeleteBuffers(1, &m_renderer_ID);}
	//non-copyable
	VertexBuffer(const VertexBuffer& other) = delete;
	VertexBuffer& operator=(const VertexBuffer& other) = delete;

	//move constructor
	VertexBuffer(VertexBuffer&& other) noexcept
		:m_renderer_ID{ std::move(other.m_renderer_ID) }
	{
		other.m_renderer_ID = 0;
	}
	//move assignment
	VertexBuffer& operator=(VertexBuffer&& other) noexcept
	{
		if (this != &other)
		{
			//free resources
			glDeleteBuffers(1, &m_renderer_ID);
			//transfer
			m_renderer_ID = std::move(other.m_renderer_ID);
			//leave other in valid state
			other.m_renderer_ID = 0;
		}
		return *this;
	}

	VertexBuffer(const float vertices[], unsigned int size);
	VertexBuffer(const std::vector<float>& vertices); //overload for meshes

	void Bind() const;
	void Unbind() const;

	const BufferLayout& GetLayout() const { return m_layout; }
	void SetLayout(const BufferLayout& layout) { m_layout = layout; }
};



//----------------
//Index Buffer
//-----------------------

class IndexBuffer
{
private:
	unsigned int m_renderer_ID;
	unsigned int m_count;
public:

	~IndexBuffer() { glDeleteBuffers(1, &m_renderer_ID); };
	//noon-copyable
	IndexBuffer(const IndexBuffer& other) = delete;
	IndexBuffer& operator=(const IndexBuffer& other) = delete;

	//move constructor
	IndexBuffer(IndexBuffer&& other) noexcept
		:m_renderer_ID{ std::move(other.m_renderer_ID) }, m_count{std::move(other.m_count)}
	{
		other.m_renderer_ID = 0;
	}
	//move assignment
	IndexBuffer& operator=(IndexBuffer&& other) noexcept
	{
		if (this != &other)
		{
			//free resources
			glDeleteBuffers(1, &m_renderer_ID);
			//transfer
			m_renderer_ID = std::move(other.m_renderer_ID);
			//leave other in valid state
			other.m_renderer_ID = 0;
			other.m_count = 0;
		}
		return *this;
	}

	IndexBuffer(const unsigned int indices[], unsigned int size); //size vs count...
	IndexBuffer(const std::vector<unsigned int>& indices); //size vs count...

	const unsigned int Count() const { return m_count; }
	void Bind() const;
	void Unbind() const;

};


#endif // !VERTEX_BUFFER_H