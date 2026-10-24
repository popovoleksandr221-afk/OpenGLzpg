#version 330 core

in vec3 fragPosition;
in vec3 fragNormal;
in vec3 lightDirection;
in vec3 vertexColor;

out vec4 FragColor;

void main()
{
    vec3 N = normalize(fragNormal);
    vec3 L = normalize(lightDirection);

    // Lambert diffuse lighting only.
    float diffuse = max(dot(N, L), 0.0);
    FragColor = vec4(vertexColor * diffuse, 1.0);
}
