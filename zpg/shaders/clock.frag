#version 330 core

in vec3 vertexColor;
in vec3 vertexNormal;

out vec4 FragColor;
uniform float brightnessScale = 1.0;

void main()
{
    vec3 displayColor = vertexColor;

    // Make the black body visible
    if (length(vertexColor) < 0.01)
    {
        displayColor = vec3(
            0.16, 0.18, 0.22
        );
    }

    float brightness =
        0.75 +
        0.25 * abs(normalize(vertexNormal).z);

    FragColor = vec4(
        displayColor * brightness * brightnessScale,
        1.0
    );
}
