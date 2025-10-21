#pragma once
#include <glm/vec3.hpp>

#include "Shader.h"

class Material {
public:
    Material(
        const glm::vec3& ambient,
        const glm::vec3& diffuse,
        const glm::vec3& specular,
        float shininess
    );

    void Use(Shader& shader) const;

private:
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;
    float Shininess;
};
