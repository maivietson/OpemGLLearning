#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

#include <GL\glew.h>			// Include glew to get all the required OpenGL headers

class Shader
{
public:
	// The program ID
	GLuint Program;
	// The attributes/uniform location ID
	GLint uniColor;
	// Constructor reads and builds the shader
	Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);
	// Get location of attributes/uniform
	void getLocationAttribAndUnif();
	// Use the program
	void Use();
	// Load Shader
	const GLchar* LoadShader(const GLchar* fileName);
};

#endif