#version 330 core

// sphere.h: position (3 floats) and normal (3 floats).
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 worldLightPosition = vec3(0.0);

out vec3 fragPosition;
out vec3 fragNormal;
out vec3 lightDirection;
out vec3 vertexColor;
out vec3 vertexPosition;

void main()
{
    vec4 worldPosition = modelMatrix * vec4(position, 1.0);
    vec4 viewPosition = viewMatrix * worldPosition;

    // a) Incorrect: w = 1 adds the sphere's translation to its normal.
    // vec3 worldNormal = normalize((modelMatrix * vec4(normal, 1.0)).xyz);

    // b) Correct: transform the normal with the inverse-transpose matrix.
    vec3 worldNormal = normalize(transpose(inverse(mat3(modelMatrix))) * normal);

    // Calculate all lighting in camera space.
    fragPosition = viewPosition.xyz;
    fragNormal = mat3(viewMatrix) * worldNormal;

    // Transform the world-space light into camera space.
    vec3 lightPosition = (viewMatrix * vec4(worldLightPosition, 1.0)).xyz;
    lightDirection = lightPosition - fragPosition;

    // Same blue material on all four spheres.
    vertexColor = vec3(0.40, 0.68, 0.90);
    vertexPosition = position;

    gl_Position = projectionMatrix * viewPosition;
}
