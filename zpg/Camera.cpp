#include "Camera.h"
#include "ICameraObserver.h"

#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
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
    return glm::lookAt(eye, center, up);
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return glm::perspective(
        glm::radians(fov), aspectRatio, nearPlane, farPlane
    );
}

void Camera::addObserver(ICameraObserver& observer)
{
    // Prevent duplicate subscriptions.
    if (std::find(observers.begin(), observers.end(), &observer) != observers.end())
    {
        return;
    }

    observers.push_back(&observer);

    // Immediately send the current matrices to new observers.
    observer.onCameraChanged(getViewMatrix(), getProjectionMatrix());
}

void Camera::removeObserver(ICameraObserver& observer)
{
    observers.erase(
        std::remove(observers.begin(), observers.end(), &observer),
        observers.end()
    );
}

void Camera::notifyObservers()
{
    const glm::mat4 view = getViewMatrix();
    const glm::mat4 projection = getProjectionMatrix();

    for (ICameraObserver* observer : observers)
    {
        observer->onCameraChanged(view, projection);
    }
}

void Camera::resize(int width, int height)
{
    if (width <= 0 || height <= 0)
    {
        return;
    }

    aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    notifyObservers();
}

void Camera::move(float forwardInput, float rightInput, float deltaTime)
{
    // Keep walking on the horizontal XZ plane.
    glm::vec3 forward = center - eye;
    forward.y = 0.0f;
    forward = glm::normalize(forward);

    const glm::vec3 right = glm::normalize(glm::cross(forward, up));
    const glm::vec3 direction = forward * forwardInput + right * rightInput;

    // Prevent faster diagonal movement.
    if (glm::length(direction) > 0.0f)
    {
        const glm::vec3 movement =
            glm::normalize(direction) * moveSpeed * deltaTime;

        eye += movement;
        center += movement;
        notifyObservers();
    }
}

void Camera::lookAround(double deltaX, double deltaY)
{
    yaw += static_cast<float>(deltaX) * mouseSensitivity;
    pitch += static_cast<float>(deltaY) * mouseSensitivity;

    pitch = glm::clamp(pitch, -85.0f, 85.0f);

    const float yawRadians = glm::radians(yaw);
    const float pitchRadians = glm::radians(pitch);

    const glm::vec3 direction(
        std::cos(yawRadians) * std::cos(pitchRadians),
        std::sin(pitchRadians),
        std::sin(yawRadians) * std::cos(pitchRadians)
    );

    center = eye + glm::normalize(direction);
    notifyObservers();
}
