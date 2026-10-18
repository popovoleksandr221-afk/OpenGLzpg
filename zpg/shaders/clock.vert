#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform float secondAngle;
uniform float minuteAngle;
uniform float hourAngle;

out vec3 vertexColor;
out vec3 vertexNormal;

mat3 rotationZ(float angle)
{
    float c = cos(angle);
    float s = sin(angle);

    return mat3(
         c,  s, 0.0,
        -s,  c, 0.0,
         0.0, 0.0, 1.0
    );
}

void main()
{
    float angle = 0.0;

    // Red vertices represent the second hand
    if (color.r > 0.5 && color.g < 0.5 && color.b < 0.5)
    {
        angle = -secondAngle;
    }
    // Green vertices represent the minute hand
    else if (color.g > 0.5 && color.r < 0.5 && color.b < 0.5)
    {
        angle = -minuteAngle;
    }
    // Blue vertices represent the hour hand
    else if (color.b > 0.5 && color.r < 0.5 && color.g < 0.5)
    {
        angle = -hourAngle;
    }

    mat3 rotation = rotationZ(angle);

    vec3 newPosition = rotation * position;
    vec3 newNormal = rotation * normal;

    // Correct the mirrored clock face
    newPosition.x = -newPosition.x;
    newNormal.x = -newNormal.x;

    gl_Position =
        projectionMatrix *
        viewMatrix *
        modelMatrix *
        vec4(newPosition, 1.0);

    vertexColor = color;
    vertexNormal = newNormal;
}