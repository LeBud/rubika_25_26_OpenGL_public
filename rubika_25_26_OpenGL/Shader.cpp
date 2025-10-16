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
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //Get file
    std::string vertexCode = LoadVertexShader(vertexPath);
    char const* vertexCodeChar = vertexCode.c_str();
    
    //Compile the Vertex Shader
    glShaderSource(vertexShader, 1, &vertexCodeChar, NULL);
    glCompileShader(vertexShader);

    //Check if Vertex Shader successfully compile
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Vertex shader compilation failed: " << infoLog << std::endl;
        return false;
    }

    
    //Create the Shaders
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    //Get file
    std::string fragmentCode = LoadFragShader(fragmentPath);
    char const* fragmentCodeChar = fragmentCode.c_str();
    
    //Compile the Frag Shader
    glShaderSource(fragmentShader, 1, &fragmentCodeChar, NULL);
    glCompileShader(fragmentShader);

    //Check if Frag Shader successfully compile
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Fragment shader compilation failed: " << infoLog << std::endl;
        return false;
    }
    
    
    //Create a Program
    ProgramID = glCreateProgram();

    //Attach the shader to the program
    glAttachShader(ProgramID, vertexShader);
    glAttachShader(ProgramID, fragmentShader);

    //Link the shader to the program
    glLinkProgram(ProgramID);

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

void Shader::Use() {
    //Use the program -- It is used here because we want to use the program only on the current draw
    glUseProgram(ProgramID);

    //Program is modify after it is being use
    SetFloat("iTime", glfwGetTime());
}


void Shader::SetInt(const std::string& name, int value) const {
    int loc = glGetUniformLocation(ProgramID, name.c_str());
    glUniform1i(loc, value);
}

void Shader::SetFloat(const std::string& name, float value) const {
    int loc = glGetUniformLocation(ProgramID, name.c_str());
    glUniform1f(loc, value);
}

void Shader::SetVec2(const std::string& name, float x, float y) const {
    int loc = glGetUniformLocation(ProgramID, name.c_str());
    glUniform2f(loc, x, y);
}

void Shader::SetVec3(const std::string& name, float x, float y, float z) const {
    int loc = glGetUniformLocation(ProgramID, name.c_str());
    glUniform3f(loc, x, y, z);
}

void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const {
    int loc = glGetUniformLocation(ProgramID, name.c_str());
    glUniform4f(loc, x, y, z, w);
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
