#include "Window.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Geometric.h"

Window* Window::_windowInstance = nullptr;

WindowInfo::WindowInfo()
{
	this->title = "Default";
	this->position_x = 0;
	this->position_y = 0;
	this->width = 800;
	this->height = 600;
	this->flag = SDL_WINDOW_OPENGL;
}

WindowInfo::WindowInfo(const WindowInfo& _info)
{
	this->title = _info.title;
	this->position_x = _info.position_x;
	this->position_y = _info.position_y;
	this->width = _info.width;
	this->height = _info.height;
	this->flag = _info.flag;
}

Window::Window(WindowInfo _info) {
	this->windowInfo = _info;
	try
	{
		SDL_Init(SDL_INIT_VIDEO);
		this->window = SDL_CreateWindow(this->windowInfo.title,
			this->windowInfo.position_x, this->windowInfo.position_y,
			this->windowInfo.width, this->windowInfo.height, this->windowInfo.flag);
		if (window == nullptr)
			throw SDL_GetError();
		else {
			this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
			this->glContext = SDL_GL_CreateContext(this->window);
			glewExperimental = GL_TRUE;
			if (glewInit() != GLEW_OK) {
				throw "Failed to initialize GLEW.";
			}
			else {
				std::cout << "Initialize GLEW successfully." << std::endl;
			}
		}
	}
	catch (const char* error)
	{
		std::cout << "CATCH IN WINODW::WINDOW(WINDOWINFO _INFO) FUNCTION: " << error << std::endl;
		throw;
	}
	
}

void Window::PrintInfo()
{
	std::cout << "=== PRINT THIS WINDOW'S INFO ===" << std::endl;
	std::cout << "TITLE: " << this->windowInfo.title << std::endl;
	std::cout << "POSITION_X: " << this->windowInfo.position_x << std::endl;
	std::cout << "POSITION_Y: " << this->windowInfo.position_y << std::endl;
	std::cout << "WIDTH: " << this->windowInfo.width << std::endl;
	std::cout << "HEIGHT: " << this->windowInfo.height << std::endl;
	std::cout << "FLAG: " << this->windowInfo.flag << std::endl;
	std::cout << "=== PRINT END ===" << std::endl;
}

void Window::LoadModel()
{
	std::cout << "LOAD MODEL." << std::endl;

}

void Window::Loop()
{
	std::cout << "GAME LOOP." << std::endl;
	
	Painter painter;
	Cube cube;
	Triangle triangle;
	GLuint programID = Shader::LoadShaders("SimpleVertexShader.vertexshader",
		"SimpleFragmentShader.fragmentshader");

	glm::mat4 Projection = glm::perspective(glm::radians(45.0f),
		(float)this->windowInfo.width / (float)this->windowInfo.height, 0.1f, 100.0f);

	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);

	glm::mat4 Model = glm::mat4(1.0f);

	glm::mat4 mvp = Projection * View * Model;

	

	while (true) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				break;
		}
		glClearColor(0, 1, 2, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLuint MatrixID = glGetUniformLocation(programID, "MVP");

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		glUseProgram(programID);

		painter.Draw(cube, 36);

		SDL_GL_SwapWindow(this->window);
	}
}

void Window::Destory()
{
	SDL_GL_DeleteContext(this->glContext);
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

void Window::SetInstance(WindowInfo _info)
{
	if (_windowInstance == nullptr)
		_windowInstance = new Window(_info);
}
