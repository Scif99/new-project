#include "framebuffer.h"

Framebuffer::Framebuffer(unsigned int width, unsigned int height)
	:m_texture_object{width, height}, m_renderbuffer{width, height}
{
	glGenFramebuffers(1, &m_frame_buffer_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_ID);

	AttachTextureObject(width, height);
	AttachRenderbufferObject();

	//Check we have successufully set up the framebuffer
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0); //make sure to unbind to we dont accidentally render to wrong framebuffer
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &m_frame_buffer_ID);
}

//Attach a texture image as a color attachment (since we probably want to read color values in shader)
void Framebuffer::AttachTextureObject(int width, int height)
{
	// attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture_object.m_renderer_ID, 0);
}

//Attach a renderbuffer object image as the stencil/depth attachments 
void Framebuffer::AttachRenderbufferObject()
{
	//can attach to stencil & depth together.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderbuffer.m_renderer_ID); //attach to the stencil&depth attachments (can do it in one go!)
}