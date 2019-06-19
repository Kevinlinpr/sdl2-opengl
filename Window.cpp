#include "Window.h"
#include "Triangle.h"
#include "loadShader.cpp"

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

void Window::Loop()
{
	Triangle* triangle = new Triangle;
	GLuint programID = triangle->LoadShaders("SimpleVertexShader.vertexshader",
		"SimpleFragmentShader.fragmentshader");

	
	while (true) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				break;
		}
		glClearColor(0, 1, 2, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		triangle->Draw();

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
