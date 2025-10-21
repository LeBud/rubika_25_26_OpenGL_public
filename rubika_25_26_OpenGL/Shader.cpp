#include "Shader.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <GLFW/glfw3.h>

Shader::Shader() {
}

Shader::~Shader() {
    glDeleteProgram(ProgramID);
}

bool Shader::Init(const char* vertexPath, const char* fragmentPath) {
    //Create the Shaders
    vertexShader = CreateShader(vertexPath, GL_VERTEX_SHADER);
    fragmentShader = CreateShader(fragmentPath, GL_FRAGMENT_SHADER);
    
    //Create a Program
    ProgramID = glCreateProgram();

    //Attach the shader to the program
    glAttachShader(ProgramID, vertexShader);
    glAttachShader(ProgramID, fragmentShader);

    //Link the shader to the program
    glLinkProgram(ProgramID);

    int success;
    char infoLog[512];
    
    //Check if the shader is successfully link to the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ProgramID, 512, NULL, infoLog);
        std::cout << "Program linking failed: " << infoLog << std::endl;
        return false;
    }

    //Delete the shader that are now stored in the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

unsigned int Shader::CreateShader(const char* path, GLenum type) {
    //Create the Shaders
    GLuint shader = glCreateShader(type);

    //Get file
    std::string shaderCode = LoadVertexShader(path);
    char const* shaderCodeChar = shaderCode.c_str();
    
    //Compile the Vertex Shader
    glShaderSource(shader, 1, &shaderCodeChar, NULL);
    glCompileShader(shader);

    //Check if Vertex Shader successfully compile
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Vertex shader compilation failed: " << infoLog << std::endl;
        return -1;
    }

    return shader;
}


void Shader::Use() {
    //Use the program -- It is used here because we want to use the program only on the current draw
    glUseProgram(ProgramID);
}

void Shader::SetInt(const std::string& name, int value) const {
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetFloat(const std::string& name, float value) const {
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetVec2(const std::string& name, float x, float y) const {
    glUniform2f(GetUniformLocation(name), x, y);
}

void Shader::SetVec2(const std::string& name, glm::vec2 vector) const {
    glUniform2f(GetUniformLocation(name), vector.x, vector.y);
}

void Shader::SetVec3(const std::string& name, float x, float y, float z) const {
    glUniform3f(GetUniformLocation(name), x, y, z);
}

void Shader::SetVec3(const std::string& name, glm::vec3 vector) const {
    glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
}

void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const {
    glUniform4f(GetUniformLocation(name), x, y, z, w);
}

void Shader::SetVec4(const std::string& name, glm::vec4 vector) const {
    glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

int Shader::GetUniformLocation(const std::string& name) const {
    return glGetUniformLocation(ProgramID, name.c_str());
}

void Shader::MatrixUpdate() {
    // retrieve the matrix uniform locations
    unsigned int modelLoc = glGetUniformLocation(ProgramID, "model");
    unsigned int viewLoc  = glGetUniformLocation(ProgramID, "view");
    
    // pass them to the shaders (3 different ways)
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
}

std::string Shader::LoadVertexShader(const char* vertexPath) {
    //Open file at path VertexPath
    std::string vertexCode;
    std::ifstream vertexStream(vertexPath, std::ios::in);
    if (vertexStream.is_open()) {
        std::stringstream sstr;
        sstr << vertexStream.rdbuf();
        vertexCode = sstr.str();
        vertexStream.close();
    }else {
        std::cout << "Failed to open the vertex shader" << std::endl;
        return vertexCode;
    }

    //Return a string if vertexCode
    return vertexCode;
}

std::string Shader::LoadFragShader(const char* fragmentPath) {
    //Open file at path VertexPath
    std::string fragCode;
    std::ifstream fragStream(fragmentPath, std::ios::in);
    if (fragStream.is_open()) {
        std::stringstream sstr;
        sstr << fragStream.rdbuf();
        fragCode = sstr.str();
        fragStream.close();
    }else {
        std::cout << "Failed to open the frag shader" << std::endl;
        return fragCode;
    }

    //Return a string of fragCode
    return fragCode;
}
