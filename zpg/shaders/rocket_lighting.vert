#version 330 core

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

    fragPosition = viewPosition.xyz;
    fragNormal = normalize(mat3(transpose(inverse(modelView))) * normal);

    vec3 sunPosition = (viewMatrix * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
    lightDirection = sunPosition - fragPosition;

    // Simple rocket colors without extra materials or textures.
    vertexColor = vec3(0.82, 0.86, 0.95);
    if (position.y > 2.75)
        vertexColor = vec3(0.95, 0.18, 0.12);
    else if (position.y < 0.35)
        vertexColor = vec3(0.25, 0.28, 0.34);
    else if (position.y < 1.35 &&
             (abs(position.x) > 0.38 || abs(position.z) > 0.38))
        vertexColor = vec3(0.88, 0.22, 0.15);

    gl_Position = projectionMatrix * viewPosition;
}
