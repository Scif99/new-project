#include "Shader.h"

#include <glm/glm.hpp>


void GLShader::Compile(const char* vShaderCode, const char* fShaderCode)
{
    // create shader objects
    unsigned int vertex, fragment;

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    // Link Shaders
    m_renderer_ID = glCreateProgram();
    glAttachShader(m_renderer_ID, vertex);
    glAttachShader(m_renderer_ID, fragment);
    glLinkProgram(m_renderer_ID);
    CheckCompileErrors(m_renderer_ID, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

GLShader::GLShader(const char* vertexPath, const char* fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    
    try
    {
        std::ifstream vShaderFile(vertexPath);
        std::ifstream fShaderFile(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    Compile(vShaderCode, fShaderCode);
}

void GLShader::Use()
{
    glUseProgram(m_renderer_ID);
}

void GLShader::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_renderer_ID, name.c_str()), (int)value);
}
void GLShader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_renderer_ID, name.c_str()), value);
}
void GLShader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_renderer_ID, name.c_str()), value);
}

void GLShader::SetVec3(const std::string& name, const glm::vec3& vec) const
{
    glUniform3fv(glGetUniformLocation(m_renderer_ID, name.c_str()), 1, &vec[0]);
}

void GLShader::SetMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_renderer_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void GLShader::CheckCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}