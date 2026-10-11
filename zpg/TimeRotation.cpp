
#include "TimeRotation.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

TimeRotation::TimeRotation(
    const glm::vec3& axisValue,
    float speedValue,
    float initialAngleValue)
    : axis(glm::normalize(axisValue)),
    speed(speedValue),
    initialAngle(initialAngleValue)
{
}

glm::mat4 TimeRotation::getModelMatrix() const
{
    float time = static_cast<float>(glfwGetTime());

    float angle = initialAngle + time * speed;

    return glm::rotate(
        glm::mat4(1.0f),
        angle,
        axis
    );
}
