#include "resource_manager.h"

/*
- Note that Shader/Texture do not have default constructors, so we use insert()/at() rather than using []
*/

std::shared_ptr<GLShader> ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile , std::string name)
{
    //assert(!Shaders.contains(name) && "Shader already exists!");
    Shaders[name] = std::make_shared<GLShader>(vShaderFile, fShaderFile);
	return Shaders[name];
}

std::shared_ptr<GLShader> ResourceManager::GetShader(const std::string& name)
{
    //assert(Shaders.contains(name));
	return Shaders[name];
}
std::shared_ptr<GLTexture> ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
{
    //assert(!Textures.contains(name) && "Texture already exists!");
    Textures[name] = std::make_shared<GLTexture>(file, alpha);
    return Textures[name];
}

std::shared_ptr<GLTexture> ResourceManager::LoadTexture(unsigned char r, unsigned char g, unsigned char b, std::string name)
{
    //assert(!Textures.contains(name) && "Texture already exists!");
    Textures[name] = std::make_shared<GLTexture>(r,g,b);
    return Textures[name];
}

 
std::shared_ptr<GLTexture> ResourceManager::GetTexture(const std::string& name)
{
    //assert(Shaders.contains(name));
	return Textures[name];
}

void ResourceManager::clear()
{
    // (properly) delete all shaders	
    for (auto& iter : Shaders)
        glDeleteProgram(iter.second->m_renderer_ID);
    // (properly) delete all textures
    for (auto& iter : Textures)
        glDeleteTextures(1, &iter.second->m_renderer_ID);
}