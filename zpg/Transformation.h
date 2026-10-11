
#pragma once

#include "TransformationComponent.h"

class Transformation : public TransformationComponent
{
private:
    float offsetX;
    float offsetY;
    float offsetZ;

    float scale;
    float rotationY;

public:
    Transformation();

    Transformation(
        float x,
        float y,
        float z,
        float scaleValue,
        float rotationYValue
    );

    float getOffsetX() const;
    float getOffsetY() const;
    float getOffsetZ() const;

    float getScale() const;
    float getRotationY() const;

    void translate(
        float x,
        float y,
        float z
    );

    void changeScale(float value);

    void rotateY(float angle);

    glm::mat4 getModelMatrix() const override;
};
