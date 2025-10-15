#include "Threshold.h"

#include <iostream>
#include <__msvc_ostream.hpp>
#include <glad/glad.h>

#include "Shader.h"

namespace threshold
{
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	Shader* shaderProgram;
	
	float vertices[] = {	// rectangle
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
	   -0.5f, -0.5f, 0.0f,  // bottom left
	   -0.5f,  0.5f, 0.0f   // top left 
   };
	
	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};  
	
	void init()
	{
		//Create the VAO (Vertex Array Object) and Bind
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		//Create the VBO (Vertex Buffer Object) and Bind
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		//Create the EBO (Element Buffer Object) and Bind
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		
		//Send Buffer Data to the GPU - Vertices
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//Copy our index array in a Element Buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//Set the vertex attributes Pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		
		//Shader class ici
		if (shaderProgram == nullptr)
			shaderProgram = new Shader();
		
		if (!shaderProgram->Init("./Ressources/default.glslv", "./Ressources/default.glslf")) {
			std::cout << "Failed to initialize the shader program" << std::endl;
		}
		
	}

	void update()
	{
		// useless for now
	}

	void draw()
	{
		shaderProgram->Use();

		//Bind the VAO i want to draw
		glBindVertexArray(VAO);

		//Draw the rectangle
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}

	void destroy()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		delete shaderProgram;
	}
}
