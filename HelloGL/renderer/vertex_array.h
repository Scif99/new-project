#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <glad/glad.h>
#include <memory>
#include "buffer.h"

class VertexArray
{

private:
	unsigned int m_renderer_ID;
	std::vector<std::shared_ptr<VertexBuffer>> m_vertex_buffers;
	std::shared_ptr<IndexBuffer> m_index_buffer;

public:
	VertexArray();
	~VertexArray(){ glDeleteVertexArrays(1, &m_renderer_ID); }

	VertexArray(const VertexArray& other) = delete;
	VertexArray& operator=(const VertexArray& other) = delete;

	VertexArray(VertexArray&& other) noexcept
		:m_renderer_ID{ std::move(other.m_renderer_ID) }, m_vertex_buffers{std::move(other.m_vertex_buffers)}, m_index_buffer{std::move(other.m_index_buffer)}
	{
		other.m_renderer_ID = 0;
	}
	VertexArray& operator=(VertexArray&& other) noexcept
	{
		if (this != &other)
		{
			//release resources
			glDeleteVertexArrays(1, &m_renderer_ID);

			//transfer
			m_renderer_ID = std::move(other.m_renderer_ID);
			m_vertex_buffers = std::move(other.m_vertex_buffers);
			m_index_buffer = std::move(other.m_index_buffer);

			//leave in valid state
			other.m_renderer_ID = 0;
		}
		return *this;
	}

	void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo);
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ibo);

	const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const{ return m_vertex_buffers; }
	const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const{ return m_index_buffer; }


	void Bind() const;
	void Unbind() const;
};

#endif // !VERTEX_ARRAY_H
