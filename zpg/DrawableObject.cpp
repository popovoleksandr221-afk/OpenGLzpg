
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

    glm::mat4 modelMatrix =
        transformation.getModelMatrix();

    for (const Transformation& t : transformations)
    {
        modelMatrix =
            modelMatrix * t.getModelMatrix();
    }

    shaderProgram->setUniform(
        "modelMatrix",
        modelMatrix
    );

    model->draw();
}

void DrawableObject::setTransformation(
    const Transformation& value)
{
    transformation = value;

    transformations.clear();
}

void DrawableObject::addTransformation(
    const Transformation& value)
{
    transformations.push_back(value);
}

void DrawableObject::translate(
    float x,
    float y,
    float z)
{
    transformation.translate(x, y, z);
}

void DrawableObject::changeScale(float value)
{
    transformation.changeScale(value);
}

void DrawableObject::rotateY(float angle)
{
    transformation.rotateY(angle);
}
