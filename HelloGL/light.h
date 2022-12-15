#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "renderer/renderer.h"

//FIX
#include "cube.h"

class LightCube
{
public:
    std::shared_ptr<CubeMesh> m_mesh;
    glm::vec3 m_position;
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

    inline static glm::vec3 s_default_pos = glm::vec3(1.2f, 1.0f, 2.0f);
    inline static glm::vec3 s_default_ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    inline static glm::vec3 s_default_diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    inline static glm::vec3 s_default_specular = glm::vec3(1.0f, 1.0f, 1.0f);
public:
    LightCube(const glm::vec3& pos, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
        : m_position{ pos }, m_ambient{ ambient }, m_diffuse{ diffuse }, m_specular{ specular }
    {
        m_mesh = std::make_shared<CubeMesh>();
    }
};
