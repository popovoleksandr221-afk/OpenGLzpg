#version 330 core

in vec3 vertexPosition;
out vec4 FragColor;

void main()
{
    // Tree coordinates in tree.h start at Y = 0.
    float radius = length(vertexPosition.xz);

    // Narrow central trunk near the ground.
    if (vertexPosition.y < 1.8 && radius < 0.38)
    {
        FragColor = vec4(0.44, 0.26, 0.10, 1.0);
    }
    else
    {
        // Small variations create several natural shades of green.
        float variation = 0.5 + 0.5 * sin(
            vertexPosition.x * 13.0 +
            vertexPosition.y * 7.0 +
            vertexPosition.z * 11.0
        );

        vec3 darkGreen = vec3(0.02, 0.35, 0.03);
        vec3 lightGreen = vec3(0.06, 0.66, 0.09);
        vec3 leaves = mix(darkGreen, lightGreen, variation);

        FragColor = vec4(leaves, 1.0);
    }
}