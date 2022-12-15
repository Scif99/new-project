#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "renderer/renderer.h"
#include "../perlin.hpp"


/*
All instances share a VBO, IBO
    - Thus
*/

class TerrainMesh
{
public:
    std::shared_ptr<VertexArray> m_VAO;
    std::shared_ptr<VertexBuffer> m_VBO;
    
    //construct with a specified number of vertices in each 
    //By default the mesh lies in the x-z plane, with a normal in the +ve y-direction
    TerrainMesh(int xVert, int zVert)
    {

        const float Xunit{ 2.f/(xVert -1)}; //distance between each vertex in x-direction
        const float Zunit{ 2.f / (zVert - 1) };//distance between each vertex in z-direction

        std::vector<float> vertices;
        vertices.reserve(xVert * zVert);
        for (int z = 0; z < zVert;++z)
        {
            for (int x = 0; x < xVert;++x)
            {
                float x_coord{-1.f + x*Xunit};
                float z_coord{-1.f + z*Zunit};
                float y_coord{0.f};

                vertices.push_back(x_coord);
                vertices.push_back(y_coord);
                vertices.push_back(z_coord);

                //Normal
                vertices.push_back(0.f);
                vertices.push_back(1.f);
                vertices.push_back(0.f);

            }
        }

        std::vector<unsigned int> indices;
        indices.reserve(xVert * zVert*3);
        for (int z = 0;z < zVert-1;++z)
        {
            for (int x = 1;x < zVert;++x)
            {
                int curr = zVert * z + x;
                indices.push_back(curr);
                indices.push_back(curr-1);
                indices.push_back(curr + xVert - 1);

                indices.push_back(curr);
                indices.push_back(curr + xVert - 1);
                indices.push_back(curr + xVert);

            }
        }

        //specify the layout of the data
        BufferLayout layout({ ShaderDataType::Float3, ShaderDataType::Float3});

        //Generate VBO, attach layout
        m_VBO = std::make_shared<VertexBuffer>(vertices);
        m_VBO->SetLayout(layout);
        auto IBO = std::make_shared<IndexBuffer>(indices);
        m_VAO = std::make_shared<VertexArray>();

        //Configure VAO
        m_VAO->Bind();
        m_VAO->AddVertexBuffer(m_VBO);
        m_VAO->SetIndexBuffer(IBO);
        m_VAO->Unbind();
        m_VBO->Unbind();
    }
    void Draw()
    {
        m_VAO->Bind();
        glDrawElements(GL_TRIANGLES, m_VAO->GetIndexBuffer()->Count(), GL_UNSIGNED_INT, 0);
        m_VAO->Unbind();
    }
};

//A simpler quad that only contains 4 vertices
//Useful for a flat textured terrain
class TerrainQuad
{
public:
    std::shared_ptr<VertexArray> m_VAO;
    std::shared_ptr<VertexBuffer> m_VBO;

    TerrainQuad()
    {

        float vertices[] = {
            //pos                //normal       //tex
           -0.5f, 0.f,-0.5f,    0.f,1.f,0.f,  0.f,0.f,
            0.5f, 0.f,-0.5f,    0.f,1.f,0.f,  1.f,0.f,
            0.5f, 0.f, 0.5f,    0.f,1.f,0.f,  1.f,1.f,
           -0.5f, 0.f, 0.5f,    0.f,1.f,0.f,  0.f,1.f
        };

        unsigned int indices[] = {
            0,2,1,
            0,3,2
        };

        //specify the layout of the data
        BufferLayout layout({ ShaderDataType::Float3, ShaderDataType::Float3, ShaderDataType::Float2 });

        //Generate VBO, attach layout
        m_VBO = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
        m_VBO->SetLayout(layout);

        auto IBO = std::make_shared<IndexBuffer>(indices, sizeof(indices));

        m_VAO = std::make_shared<VertexArray>();

        //Configure VAO
        m_VAO->Bind();
        m_VAO->AddVertexBuffer(m_VBO);
        m_VAO->SetIndexBuffer(IBO);
        m_VAO->Unbind();
        m_VBO->Unbind();

    }
    void Draw()
    {
        m_VAO->Bind();
        glDrawElements(GL_TRIANGLES, m_VAO->GetIndexBuffer()->Count(), GL_UNSIGNED_INT, 0);
        m_VAO->Unbind();
    }
};
