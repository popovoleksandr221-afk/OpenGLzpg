#pragma once

#include <glm/glm.hpp>

class Camera
{
private:
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;

    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    float yaw;
    float pitch;
    float moveSpeed;
    float mouseSensitivity;

public:
    Camera();

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void resize(int width, int height);

    void move(
        float forwardInput,
        float rightInput,
        float deltaTime
    );

    void lookAround(
        double deltaX,
        double deltaY
    );
};