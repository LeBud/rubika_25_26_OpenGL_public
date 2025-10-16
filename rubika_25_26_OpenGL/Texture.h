#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include <xstring>

class Texture {
public:
    Texture();
    ~Texture();

    unsigned int texture1;
    unsigned int texture2;
    
    // Read both file to init the vertex shader and the fragment shader
    bool Init(const char* texturePath, unsigned int textIndex);

    // Use the corresponding texture
    void Use();
};
