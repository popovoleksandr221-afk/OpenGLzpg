#include "DrawableObject.h"

DrawableObject::DrawableObject(
    Model* modelValue,
    ShaderProgram* shaderProgramValue,
    const Transformation& transformationValue)
    : model(modelValue),
    shaderProgram(shaderProgramValue),
    transformation(transformationValue)
{
}

void DrawableObject::draw()
{
    shaderProgram->use();

    shaderProgram->setUniform(
        "offset",
        transformation.getOffsetX(),
        transformation.getOffsetY(),
        transformation.getOffsetZ()
    );

    shaderProgram->setUniform(
        "scale",
        transformation.getScale()
    );

    shaderProgram->setUniform(
        "rotationY",
        transformation.getRotationY()
    );

    model->draw();
}

void DrawableObject::translate(
    float x,
    float y,
    float z)
{
    transformation.translate(
        x,
        y,
        z
    );
}

void DrawableObject::changeScale(float value)
{
    transformation.changeScale(value);
}

void DrawableObject::rotateY(float angle)
{
    transformation.rotateY(angle);
}