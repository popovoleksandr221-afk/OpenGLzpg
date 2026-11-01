#pragma once

#include <glm/glm.hpp>

class ShaderProgram;

class Light
{
public:
    glm::vec3 position{0.0f};
    glm::vec3 color{1.0f};
    float linearAttenuation = 0.0f;
    float quadraticAttenuation = 0.0f;
    float range = 0.0f;

    // Apply a point light to the shared Phong shader program.
    void apply(const ShaderProgram& program) const;
};
