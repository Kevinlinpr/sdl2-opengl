#pragma once
#include "GL/glew.h"
#include "SDL.h"
#include <iostream>


struct WindowInfo {
	WindowInfo();
	WindowInfo(const char* _title, int _position_x, int _position_y, int _width, int _height, Uint32 _flag) :
		title(_title), position_x(_position_x), position_y(_position_y), width(_width), height(_height), flag(_flag) {};
	WindowInfo(const WindowInfo& _info);
	const char* title;
	int position_x;
	int position_y;
	int width;
	int height;
	Uint32 flag;
};

class Window
{
public:
	WindowInfo windowInfo;
	SDL_GLContext glContext;
	SDL_Window* window;
	SDL_Renderer* renderer;

	void PrintInfo();
	void Loop();
	void Destory();
	static void SetInstance(WindowInfo _info);
	static Window* GetInstance() { return _windowInstance;}
private:
	Window(WindowInfo _info);
	static Window* _windowInstance;
};

