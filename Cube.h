#pragma once
#include "Geometric.h"
#include "GL/glew.h"


class Cube:public Geometric
{
public:
	Cube(GLfloat* _g_vertex_buffer_data) :Geometric(_g_vertex_buffer_data) {};
};

