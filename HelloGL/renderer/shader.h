#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <memory>

/*
- Note that our shader class is an OpenGL wrapper.
- Therefore we should ensure the class is non-copyable
*/


//--------------------
//SHADER
//---------------------

class GLShader
{
private:
    void CheckCompileErrors(unsigned int shader, std::string type);

public:
    //OpenGL ID
    unsigned int m_renderer_ID;

    //special functions
    GLShader() = default;
    ~GLShader() { glDeleteProgram(m_renderer_ID); }
    //copy operations
    GLShader(const GLShader& other) = delete;
    const GLShader& operator=(const GLShader& other) = delete;

    //move constructor
    GLShader(GLShader&& other) noexcept
        :m_renderer_ID{ std::move(other.m_renderer_ID) }
    {
        other.m_renderer_ID = 0;
    }
    //move assignment
    GLShader& operator=(GLShader&& other) noexcept
    {
        if (this != &other)
        {
            //free resources
            glDeleteProgram(m_renderer_ID);
            //transfer
            m_renderer_ID = std::move(other.m_renderer_ID);
            //leave other in valid state
            other.m_renderer_ID = 0;
        }
        return *this;
    }

    GLShader(const char* vertexPath, const char* fragmentPath);

    //compile shader 
    void Compile(const char* vShaderCode, const char* fShaderCode);
    // use/activate the shader
    void Use();
    // utility functions that set values of uniforms
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec3(const std::string& name, const glm::vec3& vec) const;
    void SetMat4(const std::string& name, const glm::mat4& mat) const;

};
#endif 

