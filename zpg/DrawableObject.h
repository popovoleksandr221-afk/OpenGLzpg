
#pragma once

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "CompositeTransformation.h"

#include <memory>

class DrawableObject
{
private:
    Model* model;
    ShaderProgram* shaderProgram;

    std::shared_ptr<Transformation> transformation;

    CompositeTransformation composite;

    float dynamicAmplitude = 0.0f;
    float dynamicSpeed = 0.0f;
    float dynamicOffsetY = 0.0f;

public:
    DrawableObject(
        Model* model,
        ShaderProgram* shaderProgram,
        const Transformation& transformation
    );

    void draw();

    void update(float time);

    void setTransformation(
        const Transformation& value
    );

    void addTransformation(
        const Transformation& value
    );

    void addTransformation(
        std::shared_ptr<TransformationComponent> value
    );

    void setDynamicVerticalMotion(
        float amplitude,
        float speed
    );

    void translate(
        float x,
        float y,
        float z
    );

    void changeScale(float value);

    void rotateY(float angle);
};
