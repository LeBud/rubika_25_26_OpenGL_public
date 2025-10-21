#include "Material.h"

Material::Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess) {
    Ambient = ambient;
    Diffuse = diffuse;
    Specular = specular;
    Shininess = shininess * 32;
}

void Material::Use(Shader& shader) const {
    shader.SetVec3("material.ambient", Ambient);
    shader.SetVec3("material.diffuse", Diffuse);
    shader.SetVec3("material.specular", Specular);
    shader.SetFloat("material.shininess", Shininess);
}
