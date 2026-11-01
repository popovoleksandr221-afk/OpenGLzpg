#include "Material.h"
#include "ShaderProgram.h"

void Material::apply(const ShaderProgram& program) const
{
    program.use();
    program.setUniform("ambientStrength", ambientStrength);
    program.setUniform("diffuseStrength", diffuseStrength);
    program.setUniform("specularStrength", specularStrength);
    program.setUniform("shininess", shininess);
    program.setUniform("forestMaterial", static_cast<float>(surface));
}
