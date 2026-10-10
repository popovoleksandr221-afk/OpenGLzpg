#include "ShaderProgram.h"

#include <glad/gl.h>

#include <cstdlib>
#include <iostream>
ShaderProgram::ShaderProgram(
    const char* vertexFile,
    const char* fragmentFile)
{
    id = glCreateProgram();

    if (id == 0)
    {
        std::cerr
            << "Unable to create shader program"
            << std::endl;

        std::exit(EXIT_FAILURE);
    }

    vertexShader =
        std::make_unique<Shader>(
            GL_VERTEX_SHADER,
            vertexFile
        );

    fragmentShader =
        std::make_unique<Shader>(
            GL_FRAGMENT_SHADER,
            fragmentFile
        );

    glAttachShader(
        id,
        vertexShader->getId()
    );

    glAttachShader(
        id,
        fragmentShader->getId()
    );

    glLinkProgram(id);

    GLint success = GL_FALSE;

    glGetProgramiv(
        id,
        GL_LINK_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[1024];

        glGetProgramInfoLog(
            id,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cerr
            << "Shader program linking failed:\n"
            << infoLog
            << std::endl;

        glDeleteProgram(id);
        id = 0;

        std::exit(EXIT_FAILURE);
    }
}

ShaderProgram::~ShaderProgram()
{
    if (id != 0)
    {
        glDeleteProgram(id);
    }
}

void ShaderProgram::use() const
{
    glUseProgram(id);
}

void ShaderProgram::setUniform(
    const char* name,
    float value) const
{
    int location =
        glGetUniformLocation(
            id,
            name
        );

    if (location == -1)
    {
        std::cerr
            << "Uniform not found: "
            << name
            << std::endl;

        return;
    }

    glUniform1f(
        location,
        value
    );
}

void ShaderProgram::setUniform(
    const char* name,
    float x,
    float y,
    float z) const
{
    int location =
        glGetUniformLocation(
            id,
            name
        );

    if (location == -1)
    {
        std::cerr
            << "Uniform not found: "
            << name
            << std::endl;

        return;
    }

    glUniform3f(
        location,
        x,
        y,
        z
    );
}

GLuint ShaderProgram::getId() const
{
    return id;
}