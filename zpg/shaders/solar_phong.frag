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
    vec3 V = normalize(-fragPosition);
    float diffuse = max(dot(N, L), 0.0);
    float specular = 0.0;
    if (diffuse > 0.0)
        specular = pow(max(dot(reflect(-L, N), V), 0.0), 32.0);
    // Low ambient preserves a clearly dark night side opposite the Sun.
    // This scene-specific material leaves the four-lighting-model demo unchanged.
    vec3 linearColor = vertexColor * (0.06 + 0.94 * diffuse)
                    + vec3(0.20 * specular);
    FragColor = vec4(pow(clamp(linearColor, 0.0, 1.0), vec3(1.0 / 2.2)), 1.0);
}
