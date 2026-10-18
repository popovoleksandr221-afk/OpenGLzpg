#version 330 core

in vec3 vertexPosition;

out vec4 FragColor;

void main()
{
    // Green tree color
    vec3 green = vec3(0.0, 0.6, 0.0);

    FragColor = vec4(green, 1.0);
}