#pragma once
#include <glad/glad.h>
#include <string>

class Shader {
public:
    Shader();
    ~Shader();
    
    // Read both file to init the vertex shader and the fragment shader
    bool Init(const char* vertexPath, const char* fragmentPath);

    // Use the corresponding program
    void Use();

    GLuint vertexShader;
    GLuint fragmentShader;

    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec2(const std::string& name, float x, float y) const;
    void SetVec3(const std::string& name, float x, float y, float z) const;
    void SetVec4(const std::string& name, float x, float y, float z, float w) const;
    
    std::string LoadVertexShader(const char* vertexPath);
    std::string LoadFragShader(const char* fragmentPath);
    
private:
    GLuint ProgramID;
    
};
