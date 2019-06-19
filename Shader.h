#pragma once
#include "GL/glew.h"
class Shader
{
public:
	static GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
};

