#pragma once
#include "../header/Shader.h"

Shader::Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath)
{
//****************************************************************************************************************//
//*                                     Open Shader File                                                         *//
//*                                                                                                              *//
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// Open files
		vShaderFile.open(vertexSourcePath);
		fShaderFile.open(fragmentSourcePath);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// Convert stream into GLchar array
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();
//*                                                                                                              *//
//****************************************************************************************************************//


//****************************************************************************************************************//
//*                                     Compile Shader                                                           *//
//*                                                                                                              *//
	// 2. Compile shaders
	GLint success;
	GLchar infoLog[512];
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	// Check for compile time errors
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	// Check log compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
//*                                                                                                              *//
//****************************************************************************************************************//


//****************************************************************************************************************//
//*                                     Link program with shader                                                 *//
//*                                                                                                              *//
	// Link shaders
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertexShader);
	glAttachShader(this->Program, fragmentShader);
	glLinkProgram(this->Program);
	// Check for linking errors
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Delete the shaders as they're linked into our program noew and no longer necessery
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
//*                                                                                                              *//
//****************************************************************************************************************//
}


//****************************************************************************************************************//
//*                                     Function Use()                                                           *//
//*                                                                                                              *//
void Shader::Use()
{
	glUseProgram(this->Program);
}
//*                                                                                                              *//
//****************************************************************************************************************//


//****************************************************************************************************************//
//*                Function getLocationAttribAndUnif() - Get Location of attribute and uniform                   *//
//*                                                                                                              *//
void Shader::getLocationAttribAndUnif()
{
	uniColor = glGetUniformLocation(this->Program, "triangleColor");
}
//*                                                                                                              *//
//****************************************************************************************************************//