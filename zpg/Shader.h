#pragma once

class Shader
{
private:
    unsigned int id;

public:
    Shader(
        unsigned int shaderType,
        const char* shaderFile
    );

    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    unsigned int getId() const;
};