
#include "DrawableObject.h"

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

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

    glm::mat4 dynamicMatrix(1.0f);

    dynamicMatrix = glm::translate(
        dynamicMatrix,
        glm::vec3(0.0f, dynamicOffsetY, 0.0f)
    );

    modelMatrix = dynamicMatrix * modelMatrix;

    shaderProgram->setUniform(
        "modelMatrix",
        modelMatrix
    );

    model->draw();
}

void DrawableObject::update(float time)
{
    dynamicOffsetY =
        dynamicAmplitude *
        std::sin(time * dynamicSpeed);
}

void DrawableObject::setDynamicVerticalMotion(
    float amplitude,
    float speed)
{
    dynamicAmplitude = amplitude;
    dynamicSpeed = speed;
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
