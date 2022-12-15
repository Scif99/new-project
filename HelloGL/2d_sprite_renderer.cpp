
#include "2d_sprite_renderer.h"

SpriteRenderer::SpriteRenderer(std::shared_ptr<GLShader> shader)
    : m_shader{ shader }
{
    float vertices[] = {
        //pos           //tex coord
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    unsigned int indices[] = {
        0,1,2,
        3,4,5
    };


    //specify the layout of the data
    BufferLayout layout({ ShaderDataType::Float2, ShaderDataType::Float2 });

    //Generate VBO, attach layout
    auto VBO = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
    VBO->SetLayout(layout);

    //Generate IBO
    auto IBO = std::make_shared<IndexBuffer>(indices, sizeof(indices));

    //Configure VAO
    m_VAO.Bind();
    m_VAO.AddVertexBuffer(VBO);
    m_VAO.SetIndexBuffer(IBO);
    m_VAO.Unbind();
    VBO->Unbind();
}

void SpriteRenderer::DrawSprite(const std::shared_ptr<GLTexture>& texture, const glm::vec2& position,
    const glm::vec2& size, float rotate)
{

    // prepare transformations
    m_shader->Use();
    glm::mat4 model = glm::mat4(1.0f);

    //Note that the vertices are not 'centered' nicely - we actually have the top left corner at (0,0)
    //Thus all transformations will be relative to this corner...
    //This means we must be careful with transformations...
    //Alternatively we can define our vertices in a 'nicer' way
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size,1.f));

    m_shader->SetMat4("model", model);

    texture->Bind();
    

    m_VAO.Bind();
    glDrawElements(GL_TRIANGLES, m_VAO.GetIndexBuffer()->Count(), GL_UNSIGNED_INT, 0);
    m_VAO.Unbind();




}