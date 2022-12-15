#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "renderer/shader.h"
#include "renderer/texture.h"
#include "renderer/buffer.h"
#include "renderer/vertex_array.h"

class SpriteRenderer
{
public:
	std::shared_ptr<GLShader> m_shader;
	VertexArray m_VAO;
public:
	SpriteRenderer(std::shared_ptr<GLShader> shader);
	~SpriteRenderer() {};

	void DrawSprite(const std::shared_ptr<GLTexture>& texture, const glm::vec2& position,
		const glm::vec2& size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f);
};
