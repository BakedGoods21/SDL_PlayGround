#pragma once

// C++ Libraries
#include <string>

// SDL Libraries
#include <SDL.h>

namespace BakedEngine
{

enum WindowFlags
{
	INVISIBLE = 0x1,
	FULLSCREEN = 0x2,
	BORDERLESS = 0x4
};

class Window
{
public:
	Window();
	~Window();

	bool create(std::string windowName, int screenWidth, int screenHeight, uint32_t currentFlags);

	void swapBuffer();

	int getScreenWidth() { return _screenWidth; }
	int getScreenHeight() { return _screenHeight; }
private:

	bool initSdl(std::string windowName, int screenWidth, int screenHeight, uint32_t currentFlags);
	bool initGl();
	bool initGlew();

	// SDL Program
	SDL_Window* _sdlWindow = nullptr;

	// OpenGL Attributes
	SDL_GLContext _mainContext = NULL;

	int _screenWidth;
	int _screenHeight;

	//Debug??
	bool _isDoubleBufferEnabled = true;
};

} // End of namespace BakedEngine
