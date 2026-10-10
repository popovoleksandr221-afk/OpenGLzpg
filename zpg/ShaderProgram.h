#pragma once

#include "Shader.h"

#include <memory>

class ShaderProgram
{
private:
    unsigned int id;

    std::unique_ptr<Shader> vertexShader;
    std::unique_ptr<Shader> fragmentShader;

public:
    ShaderProgram(
        const char* vertexFile,
        const char* fragmentFile
    );

    ~ShaderProgram();

    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    void use() const;

    void setUniform(
        const char* name,
        float value
    ) const;

    void setUniform(
        const char* name,
        float x,
        float y,
        float z
    ) const;

    unsigned int getId() const;
};