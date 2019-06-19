#pragma once
#include "GL/glew.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

class Triangle
{
public:
	Triangle();
	void Draw();
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
	GLuint vertexArrayID;
	GLuint vertexBuffer;
	static const GLfloat g_vertex_buffer_data[];
};

