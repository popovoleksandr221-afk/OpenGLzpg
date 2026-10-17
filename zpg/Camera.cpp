#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Camera::Camera()
    : eye(0.0f, 0.0f, 3.0f),
    center(0.0f, 0.0f, 0.0f),
    up(0.0f, 1.0f, 0.0f),
    fov(45.0f),
    aspectRatio(800.0f / 600.0f),
    nearPlane(0.1f),
    farPlane(100.0f),
    yaw(-90.0f),
    pitch(0.0f),
    moveSpeed(2.0f),
    mouseSensitivity(0.12f)
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

void Camera::move(
    float forwardInput,
    float rightInput,
    float deltaTime)
{
    // Keep walking on the horizontal XZ plane
    glm::vec3 forward = center - eye;
    forward.y = 0.0f;

    forward = glm::normalize(forward);

    glm::vec3 right =
        glm::normalize(glm::cross(forward, up));

    glm::vec3 direction =
        forward * forwardInput +
        right * rightInput;

    // Prevent faster diagonal movement
    if (glm::length(direction) > 0.0f)
    {
        glm::vec3 movement =
            glm::normalize(direction) *
            moveSpeed *
            deltaTime;

        eye += movement;
        center += movement;
    }
}

void Camera::lookAround(
    double deltaX,
    double deltaY)
{
    yaw +=
        static_cast<float>(deltaX) *
        mouseSensitivity;

    pitch +=
        static_cast<float>(deltaY) *
        mouseSensitivity;

    // Prevent looking exactly straight up or down
    pitch = glm::clamp(
        pitch,
        -85.0f,
        85.0f
    );

    float yawRadians = glm::radians(yaw);
    float pitchRadians = glm::radians(pitch);

    glm::vec3 direction(
        std::cos(yawRadians) *
        std::cos(pitchRadians),

        std::sin(pitchRadians),

        std::sin(yawRadians) *
        std::cos(pitchRadians)
    );

    center = eye + glm::normalize(direction);
}