#version 330 core

in vec3 fragPosition;
in vec3 fragNormal;
in vec3 lightDirection;
in vec3 vertexColor;

out vec4 FragColor;

uniform float shininess = 32.0;
uniform float diffuseStrength = 0.90;
uniform float specularStrength = 0.30;
uniform float backfaceTest = 0.0;

void main()
{
    vec3 N = normalize(fragNormal);
    vec3 L = normalize(lightDirection);
    vec3 V = normalize(-fragPosition);

    // Ambient: the unlit side stays slightly visible.
    vec3 ambient = 0.15 * vertexColor;

    // Diffuse: Lambert's law.
    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = diffuseStrength * diff * vertexColor;

    // Phong specular: reflection toward the camera.
    vec3 R = reflect(-L, N);
    float spec = 0.0;
    if (backfaceTest > 0.5)
    {
        // Scene 7: switch between a) and b).
        // a) Incorrect: a specular highlight can appear on the unlit side.
         spec = pow(max(dot(R, V), 0.0), shininess);

        // b) Correct: suppress the highlight on the unlit side.
        //if (diff > 0.0)
        //{
       //     spec = pow(max(dot(R, V), 0.0), shininess);
       // }
    }
    else if (diff > 0.0)
    {
        spec = pow(max(dot(R, V), 0.0), shininess);
    }
    vec3 specular = specularStrength * spec * vec3(1.0);

    vec3 result = min(ambient + diffuse + specular, vec3(1.0));
    FragColor = vec4(result, 1.0);
}
