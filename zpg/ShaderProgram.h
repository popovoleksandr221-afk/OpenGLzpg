#pragma once

#include "Shader.h"
#include "ICameraObserver.h"

#include <glm/glm.hpp>
#include <memory>

class Camera;

// ShaderProgram observes a Camera and caches its matrices.
class ShaderProgram : public ICameraObserver
{
private:
    unsigned int id;

    std::unique_ptr<Shader> vertexShader;
    std::unique_ptr<Shader> fragmentShader;

    Camera* observedCamera = nullptr;
    glm::mat4 cameraView{ 1.0f };
    glm::mat4 cameraProjection{ 1.0f };
    mutable bool cameraMatricesDirty = false;

public:
    ShaderProgram(const char* vertexFile, const char* fragmentFile);
    ~ShaderProgram() override;

    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    void observeCamera(Camera& camera);
    void onCameraChanged(
        const glm::mat4& viewMatrix,
        const glm::mat4& projectionMatrix
    ) override;

    void use() const;

    void setUniform(const char* name, float value) const;
    void setUniform(const char* name, float x, float y, float z) const;
    void setUniform(const char* name, const glm::mat4& matrix) const;

    unsigned int getId() const;
};
