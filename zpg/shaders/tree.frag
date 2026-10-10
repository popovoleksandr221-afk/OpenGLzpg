#version 330 core

in vec3 vertexPosition;
in vec3 vertexNormal;

out vec4 FragColor;

void main()
{
    float distanceFromCenter =
        length(
            vec2(
                vertexPosition.x,
                vertexPosition.z
            )
        );

    float verticalNormal =
        abs(vertexNormal.y);

    if (
        vertexPosition.y < 0.32 &&
        distanceFromCenter < 0.055 &&
        verticalNormal < 0.35
    )
    {
        FragColor = vec4(
            0.36,
            0.16,
            0.05,
            1.0
        );
    }
    else
    {
        FragColor = vec4(
            0.05,
            0.45,
            0.08,
            1.0
        );
    }
}