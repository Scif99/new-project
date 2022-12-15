#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>

#include "stb_image.h"

class GLTexture
{
public:
	std::string m_path;
	unsigned int m_renderer_ID;
	int m_width{ 0 };
	int m_height{ 0 };

public:
	~GLTexture() { glDeleteTextures(1, &m_renderer_ID); }
	GLTexture() = default;
	GLTexture(const GLTexture& other) = delete;
	GLTexture& operator=(const GLTexture& other) = delete;
	
	GLTexture(GLTexture&& other) noexcept
		: m_path{ std::move(other.m_path) }, m_renderer_ID{ std::move(other.m_renderer_ID) }, m_width{ other.m_width }, m_height{ other.m_height }
	{}
	GLTexture& operator=(GLTexture&& other) noexcept
	{
		if (this != &other)
		{
			glDeleteProgram(m_renderer_ID);

			//transfer
			m_renderer_ID = std::move(other.m_renderer_ID);
			m_width =  std::move(other.m_width) ;
			m_height = std::move(other.m_height) ;
			m_path = std::move(other.m_path);

			//reset other
			other.m_renderer_ID = 0;
			other.m_width = 0;
			other.m_height = 0;
		}
		return *this;

	}

	GLTexture(const std::string& filePath, bool alpha, bool flip = true); //constructor for texture 
	GLTexture(unsigned char r, unsigned char g, unsigned char b); //overload for solid color textures
	GLTexture(int width, int height); //overload for framebuffers

	//Bind to a specified texture unit
	void Bind(unsigned int slot = 0) const;
	void Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }
};

#endif