#pragma once
#include "GL/glew.h"

class Triangle
{
public:
	Triangle();
	GLuint vertexArrayID;
	GLuint vertexBuffer;
	static const GLfloat g_vertex_buffer_data[];
};

