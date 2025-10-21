#include "Texture.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <glad/glad.h>
#include "stb/stb_image.h"

Texture::Texture() {
}

Texture::~Texture() {
}

bool Texture::Init(const char* diffusePath, const char* specularPath) {
    glGenTextures(1, &diffuseTex);
    glBindTexture(GL_TEXTURE_2D, diffuseTex);
    if (!LoadTexture(diffusePath)) {
        std::cout << "Failed to load diffuse" << std::endl;
        return false;
    }

    glGenTextures(1, &specularTex);
    glBindTexture(GL_TEXTURE_2D, specularTex);
    if (!LoadTexture(specularPath)) {
        std::cout << "Failed to load specular" << std::endl;
        return false;
    }
    
    return true;
}

bool Texture::LoadTexture(const char* texturePath) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    stbi_set_flip_vertically_on_load(true);
    
    int width, height, channels;
    unsigned char* data = stbi_load(texturePath, &width, &height, &channels, 0);

    if (data) {
        std::filesystem::path path = texturePath;
        if (path.extension() == ".png") {
            glTexImage2D(GL_TEXTURE_2D,0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else if (path.extension() == ".jpg") {
            glTexImage2D(GL_TEXTURE_2D,0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
    else {
        return false;
    }

    stbi_image_free(data);
    return true;
}

void Texture::Use() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseTex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularTex);
}
