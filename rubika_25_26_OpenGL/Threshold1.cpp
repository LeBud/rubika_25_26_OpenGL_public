#include "Threshold1.h"

#include <algorithm>
#include <iostream>
#include <__msvc_ostream.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Light.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
namespace threshold1 {

	GLuint VAO;
	GLuint VBO;
	GLuint sunVAO;

	Shader* lightShader;
	Shader* sunShader;
	Texture* textureProgram;
	Camera* camera;

	Material* emerald =
		new Material(glm::vec3(0.0215f, 0.1745f, 0.0215f),
			glm::vec3(0.07568f,0.61424f,0.07568f),
			glm::vec3(0.633f,0.727811f,0.633f), 0.6f);
	
	Material* brass=
		new Material(glm::vec3(0.329412, 0.223529, 0.027451),
			glm::vec3(0.780392,0.568627,0.113725),
			glm::vec3(0.992157,0.941176,0.807843), 0.21794872f);
	
	Material* chrome=
		new Material(glm::vec3(0.25, 0.25, 0.25),
			glm::vec3(0.4,0.4,0.4),
			glm::vec3(0.774597,0.774597,0.774597), 0.6f);

	
	struct Vertex {
		float position[3];
		float normal[3];
	};

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	
	glm::vec3 lightColor = {1.0, 1.0, 1.0};
	
	Light* light = new Light(lightPos, lightColor, 0.2f, lightColor, 0.5f, {1.0,1.0,1.0}, 1.0);
	
Vertex vertices[] = {	// cube
		// positions          // colors           // texture coords
	{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f },
{  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f },
{  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f },
{  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f },
{ -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f },
{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f },

{ -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f },
{  0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f },
{  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f },
{  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f },
{ -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f },
{ -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f },

{ -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f },
{ -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f },
{ -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f },
{ -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f },
{ -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f },
{ -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f },

{ 0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f },
{ 0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f },
{ 0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f },
{ 0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f },
{ 0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f },
{ 0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f },

{ -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f },
{  0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f },
{  0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f },
{  0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f },
{ -0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f },
{ -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f },

{ -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f },
{  0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f },
{  0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f },
{  0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f },
{ -0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f },
{ -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f }
   };
	
	void init(){
		//Create the VAO (Vertex Array Object) and Bind
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		//Create the VBO (Vertex Buffer Object) and Bind
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		
		//Send Buffer Data to the GPU - Vertices
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//Set the vertex attributes Pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		//Set the normal attributes Pointers
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);


		//====Set the VAO for the sun Cube====
		glGenVertexArrays(1, &sunVAO);
		glBindVertexArray(sunVAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//====Create lightShader (will receive light)====
		if (lightShader == nullptr)
			lightShader = new Shader();
		if (!lightShader->Init("./Shader/material.vert", "./Shader/material.frag"))
			std::cout << "Failed to initialize the shader program" << std::endl;
		
		lightShader->Use();

		//====Create the SunShader (will only serve the purpose of being a fake sun)====
		if (sunShader == nullptr)
			sunShader = new Shader();
		if (!sunShader->Init("./Shader/sun.vert", "./Shader/sun.frag"))
			std::cout << "Failed to initialize the shader program" << std::endl;

		sunShader->Use();
	}

	void update(){
		// useless for now
		lightPos = glm::vec3(sin((float)glfwGetTime()), cos((float)glfwGetTime()), sin((float)glfwGetTime())) * 2.0f;
		light->Update((float)glfwGetTime());
	}

	void draw() {
		//====Get the projection and View====
		glm::mat4 projection = glm::perspective(glm::radians(camera->GetFov()), (float)800 / (float)600, 0.1f, 100.0f);
		glm::mat4 view = camera->GetMatrix();
		
		//====Use Shader====
		lightShader->Use();

		//Light properties
		lightShader->SetVec3("viewPos", camera->GetPosition());
		light->Use(*lightShader);
		
		//Materials properties
		chrome->Use(*lightShader);

		//====Set the projection and View====
		lightShader->SetMat4("projection", projection);
		lightShader->SetMat4("view", view);

		//World Transform
		glm::mat4 model = glm::mat4(1.0f);
		lightShader->SetMat4("model", model);

		//Render Cube		
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		
		//====Draw a cube where the light is====
		
		sunShader->Use();
		sunShader->SetMat4("projection", projection);
		sunShader->SetMat4("view", view);
		
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(lightPos));
		model = glm::scale(model, glm::vec3(0.3f));
		
		sunShader->SetMat4("model", model);

		glBindVertexArray(sunVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void destroy() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		delete lightShader;
	}

	void SetCamera(Camera* cam) {
		camera = cam;
	}
}
