#version 330 core

// sphere.h: position (3 floats) and normal (3 floats).
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

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

    // Calculate all lighting in camera space.
    fragPosition = viewPosition.xyz;
    fragNormal = mat3(transpose(inverse(modelView))) * normal;

    // One light at the origin (0, 0, 0) for all four spheres.
    vec3 lightPosition = (viewMatrix * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
    lightDirection = lightPosition - fragPosition;

    // Same blue material on all four spheres.
    vertexColor = vec3(0.40, 0.68, 0.90);

    gl_Position = projectionMatrix * viewPosition;
}
