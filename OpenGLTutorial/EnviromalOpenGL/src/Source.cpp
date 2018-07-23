#include <iostream>
#include <chrono>
#include <numeric>
#include <vector>
#include <time.h>

// GLEW
#define GLEW_STATIC
#include <GL\glew.h>

// GLFW
#include <GLFW\glfw3.h>

// Other includes
#include "../header/Shader.h"

// Other Libs
#include <SOIL\SOIL.h>
// GLM Mathematics
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// variable global
GLfloat mixValue = 0.2f;

// the main function, from here we start the application and run the game loop
int main()
{
//****************************************************************************************************************//
//*                                     Setup enviroiment                                                        *//
//*                                                                                                              *//
	std::cout << "Starting GLFW context, openGL 3.3" << std::endl;
	// Init GLFW
	glfwInit();
	// Set all the require options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// initialize GLEW to setup the OpenGl Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);
//*                                                                                                              *//
//****************************************************************************************************************//


//****************************************************************************************************************//
//*                                     Create Shader Class                                                      *//
//*                                                                                                              *//
	Shader ourShader("shaders/default.vs", "shaders/default.frag");
//*                                                                                                              *//
//****************************************************************************************************************//


//****************************************************************************************************************//
//*                                     Data using in program                                                    *//
//*                                                                                                              *//
	// Set up vertex data (and buffer(s)) and attributes pointers
	GLfloat vertices2[] = {
		// Position						// Color						// Texture Coords
		 0.5f,  0.5f, 0.0f,				1.0f, 0.0f, 0.0f,				1.0f, 1.0f,					// Top Right
		 0.5f, -0.5f, 0.0f,				0.0f, 1.0f, 0.0f,				1.0f, 0.0f,					// Bottom Right
		-0.5f, -0.5f, 0.0f,				0.0f, 0.0f, 1.0f,				0.0f, 0.0f,					// Bottom Left
		-0.5f,  0.5f, 0.0f,				1.0f, 1.0f, 0.0f,				0.0f, 1.0f					// Top Left
	};
	GLuint indices[] = {				// Note that we start from 0
		0, 1, 3,						// First Triangle
		1, 2, 3							// Second Triangle
	};
	GLfloat texCoords[] = {
		0.0f, 0.0f,						// Lower-left corner
		1.0f, 0.0f,						// Lower-right corner
		0.5f, 1.0f						// Top-center corner
	};

	// Data for cube
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f
	};

	// World space positions of our cubes
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
//*                                                                                                              *//
//****************************************************************************************************************//


//****************************************************************************************************************//
//*                                     Gen & Bind Buffer and Data                                               *//
//*                                                                                                              *//
	GLuint VBO, VAO, EBO;				// VBO - Vertex Buffer Object, VAO - Vertex Array Object, EBO - Element Buffer Object
	glGenVertexArrays(1, &VAO);			// Generate VAO
	glGenBuffers(1, &VBO);				// Generate VBO
	glGenBuffers(1, &EBO);				// Generate EBO

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind the Element Buffer Object, then bind and set vertex buffer(s)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//*                                                                                                              *//
//****************************************************************************************************************//


//****************************************************************************************************************//
//*                                     Access to buffer storge data                                             *//
//*                                                                                                              *//
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// TexCoord attributes
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind VBO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
	glBindVertexArray(0);
//*                                                                                                              *//
//****************************************************************************************************************//

//****************************************************************************************************************//
//*                                    Load and create a texture                                                 *//
//*                                                                                                              *//
	GLuint texture1;
	GLuint texture2;

	//=====================================
	// Texture 1
	//=====================================
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);							// All upcoming GL_TEXTURE_2D operations now have effect on this texture object

	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load image, create texture and generate mipmaps
	int widthimg, heightimg;
	unsigned char* image = SOIL_load_image("packSource/container.jpg", &widthimg, &heightimg, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthimg, heightimg, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	//=====================================
	// Texture 2
	//=====================================
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);							// All upcoming GL_TEXTURE_2D operations now have effect on this texture object

	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load image, create texture and generate mipmaps
	image = SOIL_load_image("packSource/awesomeface.png", &widthimg, &heightimg, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthimg, heightimg, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

//*                                                                                                              *//
//****************************************************************************************************************//


//****************************************************************************************************************//
//*                                     Call Draw                                                                *//
//*                                                                                                              *//
	// get time
	auto t_start = std::chrono::high_resolution_clock::now();

	// random time
	srand((unsigned int)time(NULL));
	float ran = 1.0;

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Set the required callback functions
		glfwSetKeyCallback(window, key_callback);

		// check if any events have been activiated (key pressed, mouve moved etc.) and call corresponding reponse functions
		glfwPollEvents();

		// Render
		// clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Transfer data to uniform of fragment shader
//		auto t_now = std::chrono::high_resolution_clock::now();
//		float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

		// Active shader
		ourShader.Use();

		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);

		// Set current value of uniform mix
		glUniform1f(glGetUniformLocation(ourShader.Program, "mixValue"), mixValue);

		// Camera/View transformation
		glm::mat4 view(1.0f);
		GLfloat radius = 10.0f;
		GLfloat camX = sin(glfwGetTime()) * radius;
		GLfloat camZ = cos(glfwGetTime()) * radius;
		view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		//Projection
		glm::mat4 projection(1.0f);
		projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

		// Get their uniform location
		GLint modelLoc	= glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc	= glGetUniformLocation(ourShader.Program, "view");
		GLint projLoc	= glGetUniformLocation(ourShader.Program, "projection");
		// Pas them to the shaders
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// Note: curently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Draw container
		glBindVertexArray(VAO);
		for (GLuint i = 0; i < 10; i++)
		{
			// Calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model(1.0f);
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 2.0f * (i+1);
			model = glm::rotate(model, (GLfloat)glfwGetTime() * angle, glm::vec3(1.0f, 1.0f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
//*                                                                                                              *//
//****************************************************************************************************************//


//****************************************************************************************************************//
//*                                     Free memory                                                              *//
//*                                                                                                              *//
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
//*                                                                                                              *//
//****************************************************************************************************************//


	// Terminate GLFW, clearing nay resources allocated by GLFW
	glfwTerminate();

	return 0;
}

// Is called whenever a key is pressed/released via GLFW.
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	// Down Press
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		std::cout << key << std::endl;
		mixValue -= 0.1f;
		if (mixValue <= 0.0f)
			mixValue = 0.0f;
		std::cout << mixValue << std::endl;
	}

	// Up Press
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		std::cout << key << std::endl;
		mixValue += 0.1f;
		if (mixValue >= 1.0f)
			mixValue = 1.0f;
		std::cout << mixValue << std::endl;
	}
}