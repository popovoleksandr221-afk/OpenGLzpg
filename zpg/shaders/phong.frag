#version 330 core

in vec3 fragPosition;
in vec3 fragNormal;
in vec3 lightDirection;
in vec3 vertexColor;
in vec3 vertexPosition;

out vec4 FragColor;

uniform float shininess = 32.0;
uniform float diffuseStrength = 0.90;
uniform float specularStrength = 0.30;
uniform float backfaceTest = 0.0;
uniform float forestMaterial = 0.0;
uniform float ambientStrength = 0.15;
uniform vec3 lightColor = vec3(1.0);
uniform float linearAttenuation = 0.0;
uniform float quadraticAttenuation = 0.0;
uniform float lightRange = 0.0;

void main()
{
    vec3 N = normalize(fragNormal);
    vec3 L = normalize(lightDirection);
    vec3 V = normalize(-fragPosition);
    vec3 material = vertexColor;
    if (forestMaterial == 1.0)
    {
        float variation = 0.5 + 0.5 * sin(dot(vertexPosition, vec3(13.0, 7.0, 11.0)));
        material = mix(vec3(0.02, 0.35, 0.03), vec3(0.06, 0.66, 0.09), variation);
        if (vertexPosition.y < 1.8 && length(vertexPosition.xz) < 0.38)
            material = vec3(0.44, 0.26, 0.10);
    }
    else if (forestMaterial == 2.0)
    {
        material = vertexPosition.y < -0.1
            ? vec3(0.08, 0.28, 0.06) : vec3(0.15, 0.58, 0.10);
    }

    float distanceToLight = length(lightDirection);
    float attenuation = 1.0 / (1.0 + linearAttenuation * distanceToLight
        + quadraticAttenuation * distanceToLight * distanceToLight);
    if (lightRange > 0.0)
        attenuation *= 1.0 - smoothstep(lightRange * 0.75, lightRange, distanceToLight);

    // Ambient: the unlit side stays slightly visible.
    vec3 ambient = ambientStrength * material;

    // Diffuse: Lambert's law.
    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = diffuseStrength * diff * material;

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

    vec3 result = min(ambient + attenuation * lightColor * (diffuse + specular), vec3(1.0));
    FragColor = vec4(result, 1.0);
}
