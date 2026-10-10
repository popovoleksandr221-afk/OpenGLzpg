#version 330 core

in vec3 vertexPosition;

out vec4 FragColor;

void main()
{
    vec3 green = vec3(0.0, 0.6, 0.0);
    vec3 brown = vec3(0.45, 0.25, 0.08);

    if (vertexPosition.y < -0.5)
    {
        FragColor = vec4(brown, 1.0);
    }
    else
    {
        FragColor = vec4(green, 1.0);
    }
}