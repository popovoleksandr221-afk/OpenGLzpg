#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
    : eye(0.0f, 0.0f, 3.0f),
    center(0.0f, 0.0f, 0.0f),
    up(0.0f, 1.0f, 0.0f),
    fov(45.0f),
    aspectRatio(800.0f / 600.0f),
    nearPlane(0.1f),
    farPlane(100.0f)
{
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(
        eye,
        center,
        up
    );
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return glm::perspective(
        glm::radians(fov),
        aspectRatio,
        nearPlane,
        farPlane
    );
}

void Camera::resize(int width, int height)
{
    if (width <= 0 || height <= 0)
    {
        return;
    }

    aspectRatio =
        static_cast<float>(width) /
        static_cast<float>(height);
}