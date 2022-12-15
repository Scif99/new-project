#include "texture.h"

GLTexture::GLTexture(const std::string& filePath, bool alpha, bool flip /*= true*/)
	:m_path{filePath}
{
	if (flip) { stbi_set_flip_vertically_on_load(1); }

	int channels;
	//load image into buffer
	stbi_uc* data = NULL;
	data = stbi_load(filePath.c_str(), &m_width, &m_height, &channels, 0);
	if (!data)
	{
		std::cout << "Failed to load texture\n";
		return;
	}
	GLenum internal_format = 0, data_format = 0;
	if (channels == 3)
	{
		internal_format = GL_RGB8;
		data_format = GL_RGB;
	}
	else if (channels == 4)
	{
		internal_format = GL_RGBA8;
		data_format = GL_RGBA;
	}

	//gen/bind buffers
	glGenTextures(1, &m_renderer_ID);
	glBindTexture(GL_TEXTURE_2D, m_renderer_ID);

	// set the texture wrapping/filtering options (on the currently bound texture object
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);


	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, m_width, m_height, 0, data_format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLTexture::GLTexture(int width, int height)
	:m_width{width}, m_height{height}
{

	// generate texture
	glGenTextures(1, &m_renderer_ID);
	glBindTexture(GL_TEXTURE_2D, m_renderer_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); //note the texture has no data (it is added when we render to framebuffer!)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Clamp so we dont get any weird wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0); //unbind texture after allocating memory

}


//------------
//Alternative constructor for solid textures
//---------------------
GLTexture::GLTexture(unsigned char r, unsigned char g, unsigned char b)
{
	unsigned char data[12];	// a 2x2 texture at 24 bits 

// Store the data 
	for (int i = 0; i < 12; i += 3)
	{
		data[i] = r;
		data[i + 1] = g;
		data[i + 2] = b;
	}

	m_width = 2; m_height = 2;

	// Generate the OpenGL texture id 
	glGenTextures(1, &m_renderer_ID);

	// Bind this texture to its id 
	glBindTexture(GL_TEXTURE_2D, m_renderer_ID);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Use mipmapping filter 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Generate the texture 
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_width, m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

}


//Bind texture to a specified texture unit
void GLTexture::Bind(unsigned int slot) const
{
	assert(slot >= 0);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_renderer_ID);
}


