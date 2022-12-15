#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "renderer/renderer.h"


/*
A 2D Quad
*/
class Quad
{
public:
    std::shared_ptr<VertexArray> m_VAO;
    std::shared_ptr<VertexBuffer> m_VBO;
    std::shared_ptr<IndexBuffer> m_IBO;


    Quad()
    {

        float vertices[] = {
            // positions   // texCoords
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
             1.0f, -1.0f,  1.0f, 0.0f,
             1.0f,  1.0f,  1.0f, 1.0f
        };

        unsigned int indices[] = {
            0,1,2,
            0,2,3
        };

        //specify the layout of the data
        BufferLayout layout({ ShaderDataType::Float2, ShaderDataType::Float2 });

        //Generate VBO, attach layout
        m_VBO = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
        m_VBO->SetLayout(layout);

        m_IBO = std::make_shared<IndexBuffer>(indices, sizeof(indices));
        m_VAO = std::make_shared<VertexArray>();

        //Configure VAO
        m_VAO->Bind();
        m_VAO->AddVertexBuffer(m_VBO);
        m_VAO->SetIndexBuffer(m_IBO);
        m_VAO->Unbind();
        m_VBO->Unbind();

    }

};