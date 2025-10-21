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
	Camera* camera;

	struct Vertex {
		float position[3];
		float color[3];
		float texcoord[2];
	};
	
	Vertex vertices[] = {	// cube
		// positions          // colors           // texture coords
		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    {  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },

    { -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    {  0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    {  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    {  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    { -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },

    { -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },

    { 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    { 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },

    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    {  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    {  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    {  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    { -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },

    { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    {  0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    {  0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    { -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f }
   };


	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f), 
		glm::vec3( 2.0f,  5.0f, -15.0f), 
		glm::vec3(-1.5f, -2.2f, -2.5f),  
		glm::vec3(-3.8f, -2.0f, -12.3f),  
		glm::vec3( 2.4f, -0.4f, -3.5f),  
		glm::vec3(-1.7f,  3.0f, -7.5f),  
		glm::vec3( 1.3f, -2.0f, -2.5f),  
		glm::vec3( 1.5f,  2.0f, -2.5f), 
		glm::vec3( 1.5f,  0.2f, -1.5f), 
		glm::vec3(-1.3f,  1.0f, -1.5f)  
	};
	
	/*unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};*/ 
	
	void init()
	{
		//Create the VAO (Vertex Array Object) and Bind
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		//Create the VBO (Vertex Buffer Object) and Bind
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		//Create the EBO (Element Buffer Object) and Bind
		/*glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);*/
		
		//Send Buffer Data to the GPU - Vertices
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//Copy our index array in a Element Buffer
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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

		/*if (!textureProgram->Init("./Ressources/awesomeface.png", 1)) {
			std::cout << "Failed to initialize the texture program" << std::endl;
		}
		
		if (!textureProgram->Init("./Ressources/container.jpg", 0)) {
			std::cout << "Failed to initialize the texture program" << std::endl;
		}*/

		//Shader class ici
		if (shaderProgram == nullptr)
			shaderProgram = new Shader();
		
		if (!shaderProgram->Init("./Shader/default.glslv", "./Shader/default.glslf")) {
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

		//Use the Shader Program
		shaderProgram->Use();
		
		// pass projection matrix to shader (note that in this case it could change every frame)
		glm::mat4 projection = glm::perspective(glm::radians(camera->GetFov()), (float)800 / (float)600, 0.1f, 100.0f);
		shaderProgram->SetMat4("projection", projection);

		// camera/view transformation
		glm::mat4 view = camera->GetMatrix();
		shaderProgram->SetMat4("view", view);
		
		//Update shader parameter
		shaderProgram->SetFloat("uTime", glfwGetTime());
		
		//Bind the VAO i want to draw
		glBindVertexArray(VAO);

		//Draw triangles / Cubes
		for(unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i; 
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shaderProgram->SetMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	void destroy() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		delete shaderProgram;
	}

	void SetCamera(Camera* cam) {
		camera = cam;
	}
}
