#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform vec3 offset;
uniform float scale;
uniform float rotationY;

out vec3 vertexColor;
out vec3 vertexPosition;
out vec3 vertexNormal;

void main()
{
    float x = position.x * scale;
    float y = position.y * scale;
    float z = position.z * scale;

    float rotatedX =
        cos(rotationY) * x +
        sin(rotationY) * z;

    float rotatedY = y;

    float rotatedZ =
        -sin(rotationY) * x +
        cos(rotationY) * z;

    rotatedX += offset.x;
    rotatedY += offset.y;
    rotatedZ += offset.z;

    gl_Position = vec4(
        rotatedX,
        rotatedY,
        rotatedZ,
        1.0
    );

    vertexColor = color;

    vertexPosition = vec3(
        x,
        y,
        z
    );

    vertexNormal = color;
}