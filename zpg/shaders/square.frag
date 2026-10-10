#version 330 core

in vec3 vertexData;

out vec4 finalColor;

void main()
{
    finalColor = vec4(vertexData, 1.0);
}