
#pragma once

#include <glm/glm.hpp>

class TransformationComponent
{
public:
    virtual ~TransformationComponent() = default;

    virtual glm::mat4 getModelMatrix() const = 0;
};
