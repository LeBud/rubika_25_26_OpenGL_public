#include "Material.h"

#include <iostream>

Material::Material(const char* diffusePath, const char* specularPath, float shininess) {
    DiffusePath = diffusePath;
    SpecularPath = specularPath;
    Shininess = shininess * 32;
}

void Material::Init() {
    texture = new Texture();
    
    if (!texture->Init(DiffusePath, SpecularPath)) {
        std::cout << "Failed to initialize the Texture program" << std::endl;
    }
}

void Material::Use(Shader& shader) const {
    shader.SetFloat("material.shininess", Shininess);
    texture->Use();
}
