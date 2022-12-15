#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "texture.h"


/**
TO-DO
- add options for read/write framebufffers
-

*/

class RenderbufferObject
{
public:
	unsigned int m_renderer_ID;
	RenderbufferObject(unsigned int width, unsigned int height)
	{
		glGenRenderbuffers(1, &m_renderer_ID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_renderer_ID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0); //unbind after allocating memory
	}

	~RenderbufferObject() { glDeleteRenderbuffers(1, &m_renderer_ID); }
};


class Framebuffer
{
public:
	unsigned int m_frame_buffer_ID;
	GLTexture m_texture_object;
	RenderbufferObject m_renderbuffer;

	Framebuffer(unsigned int width, unsigned int height);

	//Attach a texture image as a color attachment (since we probably want to read color values in shader)
	void AttachTextureObject(int width, int height);

	//Attach a renderbuffer object image as the stencil/depth attachments 
	void AttachRenderbufferObject();

	void Bind() { glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_ID); }
	void Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

	~Framebuffer();

};