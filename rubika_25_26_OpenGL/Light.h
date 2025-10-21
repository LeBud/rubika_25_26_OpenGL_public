#pragma once
#include <glm/vec3.hpp>

#include "Shader.h"

class Light {
public:
    Light(); // white light at 0.0.0
    Light(
        const glm::vec3& position,
        const glm::vec3& ambient,
        float ambientIntensity,
        const glm::vec3& diffuse,
        float diffuseIntensity,
        const glm::vec3& scalar,
        float scalarIntensity
    );
    void Update(float dt);

    void Use(Shader& shader);

private:
    glm::vec3 Position;
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Scalar;
};
