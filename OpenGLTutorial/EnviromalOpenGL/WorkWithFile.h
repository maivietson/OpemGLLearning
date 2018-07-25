#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// Include glew to get all the required OpenGL headers
#include <GL\glew.h>

using namespace std;

void WorkWithFile(const GLchar* filePath, string context)
{
	ofstream streamFile;
	streamFile.exceptions(ofstream::failbit | ofstream::badbit);
	try
	{
		// open file
		streamFile.open(filePath);
		streamFile.write(context.c_str(), context.length());
		streamFile.close();
	}
	catch (ofstream::failure e)
	{
		std::cout << "ERROR::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
}