#include "Threshold.h"

#include <iostream>
#include <vcruntime.h>
#include <__msvc_ostream.hpp>
#include <glad/glad.h>

namespace threshold
{
	GLuint VertexArray;
	GLuint vertexBuffer;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	
	
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	const char* vertexShaderSource = "#version 330 core\n"
			"in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.0f, 0.25f, 1.0f);\n"
		"}\0";
	
	void init()
	{
		//Create the VAO (Vertex Array Object) and Bind
		glGenVertexArrays(1, &VertexArray);
		glBindVertexArray(VertexArray);

		//Create the VBO (Vertex Buffer Object) and Bind
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

		//Send Buffer Data to the GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		
		//Create the Shaders
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//Compile the Vertex Shader
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		//Check if successfully compile
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "Vertex shader compilation failed: " << infoLog << std::endl;
		}

		//Compile the Frag Shader
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		//Create a Program
		shaderProgram = glCreateProgram();

		//Attach the shader to the program
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);

		//Link the shader to the program
		glLinkProgram(shaderProgram);

		//Check if the shader is successfully link to the program
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "Program linking failed: " << infoLog << std::endl;
		}

		//Delete the shader that are now stored in the program
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void update()
	{
		// useless for now
	}

	void draw()
	{
		//Use the program -- It is used here because we want to use the program only on the current draw
		glUseProgram(shaderProgram);

		//Bind the VAO i want to draw
		glBindVertexArray(VertexArray);

		//Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void destroy()
	{
		glDeleteVertexArrays(1, &VertexArray);
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteProgram(shaderProgram);
	}
}
