
#pragma once

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class DrawableObject
{
private:
    Model* model;
    ShaderProgram* shaderProgram;
    Transformation transformation;

public:
    DrawableObject(
        Model* model,
        ShaderProgram* shaderProgram,
        const Transformation& transformation
    );

    void draw();

    void translate(
        float x,
        float y,
        float z
    );

    void changeScale(float value);

    void rotateY(float angle);
};
