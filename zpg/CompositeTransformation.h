
#pragma once

#include "TransformationComponent.h"

#include <memory>
#include <vector>

class CompositeTransformation : public TransformationComponent
{
private:
    std::vector<std::shared_ptr<TransformationComponent>> transformations;

public:
    void add(
        std::shared_ptr<TransformationComponent> transformation
    );

    void clear();

    glm::mat4 getModelMatrix() const override;
};
