#pragma once

class Transformation
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
        float scale,
        float rotationY
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
};