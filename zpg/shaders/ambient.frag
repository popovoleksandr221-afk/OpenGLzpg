#version 330 core

in vec3 vertexColor;
out vec4 FragColor;

void main()
{
    // Constant ambient lighting: no dependence on light direction.
    float ambientStrength = 1.0;
    FragColor = vec4(vertexColor * ambientStrength, 1.0);
}
