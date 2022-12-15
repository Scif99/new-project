#pragma once

#include <map>
#include <string>

#include "renderer/shader.h"
#include "renderer/texture.h"


/*
- Responsible for Storing/Loading Shaders & Textures
- This implementation uses the lazy-evaluated, thread-safe singleton design,
*/

class ResourceManager
{
public:
	inline static std::map<std::string, std::shared_ptr<GLShader>> Shaders;
	inline static std::map<std::string, std::shared_ptr<GLTexture>> Textures;

	static std::shared_ptr<GLShader> LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name);
	static std::shared_ptr<GLShader> GetShader(const std::string& name);
	static std::shared_ptr<GLTexture> LoadTexture(const char* file, bool alpha, std::string name);
	static std::shared_ptr<GLTexture> LoadTexture(unsigned char r, unsigned char g, unsigned char b, std::string name);
	static std::shared_ptr<GLTexture> GetTexture(const std::string& name);
public:
	static ResourceManager& Get()
	{
		static ResourceManager m_instance;
		return m_instance;
	}
	static void clear();

private:
	ResourceManager() {};

public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager operator=(const ResourceManager&) = delete;

};

