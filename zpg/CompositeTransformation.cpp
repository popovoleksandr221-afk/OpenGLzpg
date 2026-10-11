
#include "CompositeTransformation.h"

void CompositeTransformation::add(
    std::shared_ptr<TransformationComponent> transformation)
{
    if (transformation != nullptr)
    {
        transformations.push_back(transformation);
    }
}

void CompositeTransformation::clear()
{
    transformations.clear();
}

glm::mat4 CompositeTransformation::getModelMatrix() const
{
    glm::mat4 result(1.0f);

    for (const auto& transformation : transformations)
    {
        result = result * transformation->getModelMatrix();
    }

    return result;
}
