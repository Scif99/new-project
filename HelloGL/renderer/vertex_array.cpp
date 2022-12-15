#include "vertex_array.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_renderer_ID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_renderer_ID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo)
{
    assert(vbo->GetLayout().m_elements.size() && "No Layout Has Been Set!");

    glBindVertexArray(m_renderer_ID);
    vbo->Bind();

    int curr_attrib = 0;
    const auto& layout = vbo->GetLayout();
    for (const auto& attrib : layout)
    {
        glEnableVertexAttribArray(curr_attrib);
        glVertexAttribPointer(curr_attrib, attrib.GetcomponentCount(), GL_FLOAT, GL_FALSE, vbo->GetLayout().m_stride, (void*)attrib.m_offset);
        ++curr_attrib;
    }
    m_vertex_buffers.push_back(vbo);
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ibo)
{
    glBindVertexArray(m_renderer_ID);
    ibo->Bind();
    m_index_buffer = ibo;
}