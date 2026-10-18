#version 330 core

in vec3 vertexPosition;

out vec4 FragColor;

void main()
{
    // Dark green ground
    if (vertexPosition.y < -0.1)
    {
        FragColor = vec4(
            0.08, 0.28, 0.06, 1.0
        );
    }
    else
    {
        // Brighter green bushes
        FragColor = vec4(
            0.15, 0.58, 0.10, 1.0
        );
    }
}