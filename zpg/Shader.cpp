#include "Shader.h"

#include <glad/gl.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

Shader::Shader(
    unsigned int shaderType,
    const char* shaderFile)
{
    id = glCreateShader(shaderType);

    if (id == 0)
    {
        std::cerr
            << "Unable to create shader"
            << std::endl;

        std::exit(EXIT_FAILURE);
    }

    std::ifstream file(shaderFile);

    if (!file.is_open())
    {
        std::cerr
            << "Unable to open shader file "
            << shaderFile
            << std::endl;

        glDeleteShader(id);
        id = 0;

        std::exit(EXIT_FAILURE);
    }

    std::string shaderCode(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    const char* source =
        shaderCode.c_str();

    glShaderSource(
        id,
        1,
        &source,
        nullptr
    );

    glCompileShader(id);

    int success = 0;

    glGetShaderiv(
        id,
        GL_COMPILE_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[1024];

        glGetShaderInfoLog(
            id,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cerr
            << "Shader compilation failed:\n"
            << infoLog
            << std::endl;

        glDeleteShader(id);
        id = 0;

        std::exit(EXIT_FAILURE);
    }
}

Shader::~Shader()
{
    if (id != 0)
    {
        glDeleteShader(id);
    }
}

Shader::Shader(
    Shader&& other) noexcept
    : id(other.id)
{
    other.id = 0;
}

Shader& Shader::operator=(
    Shader&& other) noexcept
{
    if (this != &other)
    {
        if (id != 0)
        {
            glDeleteShader(id);
        }

        id = other.id;
        other.id = 0;
    }

    return *this;
}

unsigned int Shader::getId() const
{
    return id;
}