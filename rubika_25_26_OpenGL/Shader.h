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

    std::string LoadVertexShader(const char* vertexPath);
    std::string LoadFragShader(const char* fragmentPath);
    
private:
    GLuint ProgramID;
    
};
