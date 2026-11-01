#pragma once

class ShaderProgram;

class Material
{
public:
    enum class Surface
    {
        Plain = 0,
        Tree = 1,
        BushAndGround = 2
    };

    float ambientStrength = 0.15f;
    float diffuseStrength = 0.90f;
    float specularStrength = 0.30f;
    float shininess = 32.0f;
    Surface surface = Surface::Plain;

    // Apply the surface response and color pattern to the shared Phong shader.
    void apply(const ShaderProgram& program) const;
};
