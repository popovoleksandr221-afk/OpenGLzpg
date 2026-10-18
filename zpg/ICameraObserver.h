#pragma once

#include <glm/glm.hpp>

// Observer interface: receives updated camera matrices.
class ICameraObserver
{
public:
    virtual ~ICameraObserver() = default;

    virtual void onCameraChanged(
        const glm::mat4& viewMatrix,
        const glm::mat4& projectionMatrix
    ) = 0;
};
