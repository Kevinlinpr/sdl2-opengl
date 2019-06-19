#include "Triangle.h"

const GLfloat Triangle::g_vertex_buffer_data[] = {
	-1.0f,-1.0f,0.0f,
	1.0f,-1.0f,0.0f,
	0.0f,1.0f,0.0f
};

Triangle::Triangle()
{
	glGenVertexArrays(1, &this->vertexArrayID);
	glBindVertexArray(this->vertexArrayID);

	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->g_vertex_buffer_data), this->g_vertex_buffer_data, GL_STATIC_DRAW);
}
