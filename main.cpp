#include <iostream>
#include "Window.h"


int main(int argc, char** argv) {
	try
	{
		WindowInfo windowInfo("Game", 200, 300, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		Window::SetInstance(windowInfo);
		Window* windowInstance = Window::GetInstance();
		windowInstance->PrintInfo();
		windowInstance->LoadModel();
		windowInstance->Loop();
		windowInstance->Destory();
	}
	catch (const char* msg)
	{
		std::cout << "CATCH IN MAIN FUNCTION: " << msg << std::endl;
	}

	return 0;
}