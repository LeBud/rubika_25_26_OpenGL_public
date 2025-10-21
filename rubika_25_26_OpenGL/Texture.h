#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include <xstring>

class Texture {
public:
    Texture();
    ~Texture();

    unsigned int diffuseTex;
    unsigned int specularTex;
    
    // Read both file to init the vertex shader and the fragment shader
    bool Init(const char* diffusePath, const char* specularPath);

    bool LoadTexture(const char* texturePath);

    // Use the corresponding texture
    void Use();
};
