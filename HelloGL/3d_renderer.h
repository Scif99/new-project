#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "renderer/shader.h"
#include "renderer/texture.h"
#include "renderer/buffer.h"
#include "renderer/vertex_array.h"
#include "camera.h"
#include "light.h"

class Renderer
{
	void Clear(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a); //state-setting
	}
	void Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //state-using
	}

	void BeginScene(Camera& camera, std::vector<LightCube> lights);

	void Submit(const VertexArray& vao);
	void EndScene();

	void Draw(GLShader& shader, GLTexture& texture, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection,  const VertexArray& vao)
	{
		//Bind shader
		shader.Use();

		//pass MVP to Shader
		shader.SetMat4("model", model);
		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);

		//Texture
		texture.Bind(); //What if there is more than one texture?

		//Draw
		if (vao.GetIndexBuffer())
		{
			glDrawElements(GL_TRIANGLES, vao.GetIndexBuffer()->Count(), GL_UNSIGNED_INT, 0);
		}
			//What to do if we never used an index buffer?
	}

};