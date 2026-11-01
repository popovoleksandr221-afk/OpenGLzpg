#include "Light.h"
#include "ShaderProgram.h"

void Light::apply(const ShaderProgram& program) const
{
    program.use();
    program.setUniform("worldLightPosition", position.x, position.y, position.z);
    program.setUniform("lightColor", color.x, color.y, color.z);
    program.setUniform("linearAttenuation", linearAttenuation);
    program.setUniform("quadraticAttenuation", quadraticAttenuation);
    program.setUniform("lightRange", range);
}
