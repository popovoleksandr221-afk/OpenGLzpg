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

    // Ambient: the unlit side stays slightly visible.
    vec3 ambient = 0.15 * vertexColor;

    // Diffuse: Lambert's law.
    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = 0.90 * diff * vertexColor;

    // Phong specular: reflection toward the camera.
    vec3 R = reflect(-L, N);
    float spec = 0.0;
    if (diff > 0.0)
        spec = pow(max(dot(R, V), 0.0), 32.0);
    vec3 specular = 0.30 * spec * vec3(1.0);

    vec3 result = min(ambient + diffuse + specular, vec3(1.0));
    FragColor = vec4(result, 1.0);
}
