
#pragma once

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

#include <vector>

class DrawableObject
{
private:
    Model* model;
    ShaderProgram* shaderProgram;

    Transformation transformation;
    std::vector<Transformation> transformations;

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

    void setDynamicVerticalMotion(
        float amplitude,
        float speed
    );

    void setTransformation(
        const Transformation& value
    );

    void addTransformation(
        const Transformation& value
    );

    void translate(float x, float y, float z);
    void changeScale(float value);
    void rotateY(float angle);
};
