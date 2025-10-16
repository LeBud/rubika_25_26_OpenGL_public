#include "Threshold.h"

#include <iostream>
#include <__msvc_ostream.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Texture.h"

namespace threshold
{
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	Shader* shaderProgram;
	Texture* textureProgram;

	struct Vertex {
		float position[3];
		float color[3];
		float texcoord[2];
	};
	
	Vertex vertices[] = {	// rectangle
		// positions          // colors           // texture coords
		{  0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f }, // top right
		{  0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f }, // bottom right
		{ -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f }, // bottom left
		{ -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f }  // top left 
   };
	
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		//Set the color attributes Pointers
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		//Set the texture attributes Pointers
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		

		//Texture class ici
		if (textureProgram == nullptr)
			textureProgram = new Texture();

		if (!textureProgram->Init("./Ressources/awesomeface.png", 1)) {
			std::cout << "Failed to initialize the texture program" << std::endl;
		}
		
		if (!textureProgram->Init("./Ressources/container.jpg", 0)) {
			std::cout << "Failed to initialize the texture program" << std::endl;
		}

		//Shader class ici
		if (shaderProgram == nullptr)
			shaderProgram = new Shader();
		
		if (!shaderProgram->Init("./Ressources/default.glslv", "./Ressources/default.glslf")) {
			std::cout << "Failed to initialize the shader program" << std::endl;
		}

		shaderProgram->Use();
		shaderProgram->SetInt("texture1", 0);
		shaderProgram->SetInt("texture2", 1);
	}

	void update()
	{
		// useless for now
	}

	void draw() {
		//First bind the texture
		textureProgram->Use();
		
		//Use the Shader Program & Dynamic Update variables
		shaderProgram->Use();
		shaderProgram->SetFloat("uTime", glfwGetTime());
		//Bind the VAO i want to draw
		glBindVertexArray(VAO);

		//Draw triangles
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void destroy() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		delete shaderProgram;
	}
}
