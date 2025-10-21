#pragma once
#include <glm/vec3.hpp>

#include "Shader.h"
#include "Texture.h"

class Material {
public:
    Material(
        const char* diffusePath,
        const char* specularPath,
        float shininess
    );

    void Init();
    
    void Use(Shader& shader) const;

    Texture* texture;

private:
    const char* DiffusePath;
    const char* SpecularPath;
    float Shininess;
};
