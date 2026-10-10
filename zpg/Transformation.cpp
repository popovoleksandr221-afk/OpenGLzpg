#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>
Transformation::Transformation()
    : offsetX(0.0f),
    offsetY(0.0f),
    offsetZ(0.0f),
    scale(1.0f),
    rotationY(0.0f)
{
}

Transformation::Transformation(
    float x,
    float y,
    float z,
    float scaleValue,
    float rotationYValue)
    : offsetX(x),
    offsetY(y),
    offsetZ(z),
    scale(scaleValue),
    rotationY(rotationYValue)
{
}

float Transformation::getOffsetX() const
{
    return offsetX;
}

float Transformation::getOffsetY() const
{
    return offsetY;
}

float Transformation::getOffsetZ() const
{
    return offsetZ;
}

float Transformation::getScale() const
{
    return scale;
}

float Transformation::getRotationY() const
{
    return rotationY;
}

void Transformation::translate(float x, float y, float z)
{
    offsetX += x;
    offsetY += y;
    offsetZ += z;
}

void Transformation::changeScale(float value)
{
    scale += value;

    if (scale < 0.1f)
    {
        scale = 0.1f;
    }
}

void Transformation::rotateY(float angle)
{
    rotationY += angle;
}

glm::mat4 Transformation::getModelMatrix() const
{
    glm::mat4 model(1.0f);

    model = glm::translate(
        model,
        glm::vec3(offsetX, offsetY, offsetZ)
    );

    model = glm::rotate(
        model,
        rotationY,
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    model = glm::scale(
        model,
        glm::vec3(scale)
    );

    return model;
}