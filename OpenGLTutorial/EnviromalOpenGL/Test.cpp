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

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

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

	// Set the requireed callback functions
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
//*                                                                                                              *//
//****************************************************************************************************************//


//****************************************************************************************************************//
//*                                     Create Shader Class                                                      *//
//*                                                                                                              *//
	Shader ourShader("../shaders/default.vs", "../shaders/default.frag");
//*                                                                                                              *//
//****************************************************************************************************************//


//****************************************************************************************************************//
//*                                     Data using in program                                                    *//
//*                                                                                                              *//
	// Set up vertex data (and buffer(s)) and attributes pointers
	GLfloat vertices[] = {
		// Position						// Color
		 0.5f, -0.5f, 0.0f,				1.0f, 0.0f, 0.0f,				// Bottom Right
		-0.5f, -0.5f, 0.0f,				0.0f, 1.0f, 0.0f,				// Bottom Left
		 0.0f,  0.5f, 0.0f,				0.0f, 0.0f, 1.0f				// Top Left
	};
	GLuint indices[] = {				// Note that we start from 0
		0, 1, 2							// First Triangle
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color attributes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind VBO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
	glBindVertexArray(0);
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
		// check if any events have been activiated (key pressed, mouve moved etc.) and call corresponding reponse functions
		glfwPollEvents();

		// Render
		// clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Transfer data to uniform of fragment shader
		auto t_now = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
//		glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, ((float)rand() / (float)(RAND_MAX)) * ran, ((float)rand() / (float)(RAND_MAX)) * ran);

		// Draw our first triangle
		ourShader.Use();
		glBindVertexArray(VAO);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
}