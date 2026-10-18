#include "ShaderProgram.h"
#include "Camera.h"

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

#include <cstdlib>
#include <iostream>

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile)
    : id(0)
{
    id = glCreateProgram();

    if (id == 0)
    {
        std::cerr << "Unable to create shader program" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    vertexShader = std::make_unique<Shader>(GL_VERTEX_SHADER, vertexFile);
    fragmentShader = std::make_unique<Shader>(GL_FRAGMENT_SHADER, fragmentFile);

    glAttachShader(id, vertexShader->getId());
    glAttachShader(id, fragmentShader->getId());
    glLinkProgram(id);

    GLint success = GL_FALSE;
    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (!success)
    {
        char infoLog[1024];
        glGetProgramInfoLog(id, sizeof(infoLog), nullptr, infoLog);

        std::cerr << "Shader program linking failed:\n"
            << infoLog << std::endl;

        glDeleteProgram(id);
        id = 0;
        std::exit(EXIT_FAILURE);
    }
}

ShaderProgram::~ShaderProgram()
{
    // Camera outlives shader programs in Application.
    if (observedCamera != nullptr)
    {
        observedCamera->removeObserver(*this);
    }

    if (id != 0)
    {
        glDeleteProgram(id);
    }
}

void ShaderProgram::observeCamera(Camera& camera)
{
    if (observedCamera == &camera)
    {
        return;
    }

    if (observedCamera != nullptr)
    {
        observedCamera->removeObserver(*this);
    }

    observedCamera = &camera;
    observedCamera->addObserver(*this);
}

void ShaderProgram::onCameraChanged(

    const glm::mat4& viewMatrix,
    const glm::mat4& projectionMatrix)
{
    // OpenGL uniforms must be changed only while this program is active.
    // The observer therefore caches changes until the next use().
    cameraView = viewMatrix;
    cameraProjection = projectionMatrix;
    cameraMatricesDirty = true;
}

void ShaderProgram::use() const
{
    glUseProgram(id);

    if (cameraMatricesDirty)
    {
        setUniform("viewMatrix", cameraView);
        setUniform("projectionMatrix", cameraProjection);
        cameraMatricesDirty = false;
    }
}

void ShaderProgram::setUniform(const char* name, float value) const
{
    const GLint location = glGetUniformLocation(id, name);
    if (location == -1)
    {
        std::cerr << "Uniform not found: " << name << std::endl;
        return;
    }

    glUniform1f(location, value);
}

void ShaderProgram::setUniform(
    const char* name, float x, float y, float z) const
{
    const GLint location = glGetUniformLocation(id, name);
    if (location == -1)
    {
        std::cerr << "Uniform not found: " << name << std::endl;
        return;
    }

    glUniform3f(location, x, y, z);
}

void ShaderProgram::setUniform(const char* name, const glm::mat4& matrix) const
{
    const GLint location = glGetUniformLocation(id, name);
    if (location == -1)
    {
        std::cerr << "Uniform not found: " << name << std::endl;
        return;
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

unsigned int ShaderProgram::getId() const
{
    return id;
}
