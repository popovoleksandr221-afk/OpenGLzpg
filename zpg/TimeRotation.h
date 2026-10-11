
#pragma once

#include "TransformationComponent.h"

class TimeRotation : public TransformationComponent
{
private:
    glm::vec3 axis;
    float speed;
    float initialAngle;

public:
    TimeRotation(
        const glm::vec3& axis,
        float speed,
        float initialAngle = 0.0f
    );

    glm::mat4 getModelMatrix() const override;
};
