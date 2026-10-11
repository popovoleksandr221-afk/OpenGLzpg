
#include "DrawableObject.h"

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

DrawableObject::DrawableObject(
    Model* modelValue,
    ShaderProgram* shaderProgramValue,
    const Transformation& transformationValue)
    : model(modelValue),
    shaderProgram(shaderProgramValue),
    transformation(
        std::make_shared<Transformation>(transformationValue)
    )
{
    composite.add(transformation);
}

void DrawableObject::draw()
{
    shaderProgram->use();

    // Calculate the combined model matrix
    glm::mat4 modelMatrix =
        composite.getModelMatrix();

    // Apply the dynamic vertical movement
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
        dynamicAmplitude * std::sin(time * dynamicSpeed);
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
    *transformation = value;

    composite.clear();
    composite.add(transformation);
}

void DrawableObject::addTransformation(
    const Transformation& value)
{
    composite.add(
        std::make_shared<Transformation>(value)
    );
}

void DrawableObject::addTransformation(
    std::shared_ptr<TransformationComponent> value)
{
    composite.add(value);
}

void DrawableObject::translate(
    float x,
    float y,
    float z)
{
    transformation->translate(x, y, z);
}

void DrawableObject::changeScale(float value)
{
    transformation->changeScale(value);
}

void DrawableObject::rotateY(float angle)
{
    transformation->rotateY(angle);
}
