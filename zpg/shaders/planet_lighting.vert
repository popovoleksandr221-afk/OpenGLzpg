#version 330 core

// The planet headers contain position + RGB, NOT position + normal.
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec3 fragPosition;
out vec3 fragNormal;
out vec3 lightDirection;
out vec3 vertexColor;

void main()
{
    mat4 modelView = viewMatrix * modelMatrix;
    vec4 viewPosition = modelView * vec4(position, 1.0);
    fragPosition = viewPosition.xyz;
    // These are unit spheres centered at the origin: radial normals are exact.
    fragNormal = mat3(transpose(inverse(modelView))) * normalize(position);
    vec3 sunPosition = (viewMatrix * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
    lightDirection = sunPosition - fragPosition;
    vertexColor = color;
    gl_Position = projectionMatrix * viewPosition;
}
