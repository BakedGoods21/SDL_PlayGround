// GL Libraries
#include <GL/glew.h>

// BakedEngine Includes
#include "BakedEngine/Window.h"
#include "BakedEngine/SdlError.h"

namespace BakedEngine
{

Window::Window()
{

}

Window::~Window()
{
	// Destroy window
	if (_sdlWindow)
	{
		SDL_DestroyWindow( _sdlWindow );
	}
}

bool Window::create(std::string windowName, int screenWidth, int screenHeight, uint32_t currentFlags)
{
	bool status = initSdl(windowName, screenWidth, screenHeight, currentFlags);
	if (status) { status = initGl(); }
	if (status) { status = initGlew(); }

	// Use Vsync
	if( status && SDL_GL_SetSwapInterval( 1 ) < 0 )
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_WARNING, "Vsync Warning" ,  "Unable to set VSync, SDL_ERROR: " + std::string(SDL_GetError()));
	}

	// Check the OpenGl Version
	CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "Open GL" ,  "OpenGl Version: " + std::string((char*)glGetString(GL_VERSION)));

	// Set VSYNC
	SDL_GL_SetSwapInterval(0);

	// Enable alpha blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	return status;
}

bool Window::initSdl(std::string windowName, int screenWidth, int screenHeight, uint32_t currentFlags)
{
	uint32_t flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

	if (currentFlags & INVISIBLE)
	{
		flags |= SDL_WINDOW_HIDDEN;
	}
	if(currentFlags & FULLSCREEN)
	{
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if (currentFlags & BORDERLESS)
	{
		flags |= SDL_WINDOW_BORDERLESS;
	}

	// Destroy window if there is one already
	if (_sdlWindow)
	{
		SDL_DestroyWindow( _sdlWindow );
	}

	// Create window
	_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
	if (_sdlWindow == NULL)
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "SDL_ERROR",  "Could not Create SDL Window");
		return false;
	}

	return true;
}

bool Window::initGl()
{
	// Create context
	if (_sdlWindow)
	{
		_mainContext = SDL_GL_CreateContext( _sdlWindow );
		if (_mainContext == NULL)
		{
			CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "OPEN_GL_ERROR",  "Could not Create OpenGl Context");
			return false;
		}

		return true;
	}
	else
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "OPEN_GL_ERROR",  "SDL window not initialized");
		return false;
	}
}

bool Window::initGlew()
{
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if ( glewError != GLEW_OK )
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "GLEW Error" ,  "Could not Initialize GLEW: " + std::string((const char*)glewGetErrorString( glewError )));
		return false;
	}

	return true;
}

void Window::swapBuffer()
{
	if (_isDoubleBufferEnabled)
	{
		// Update screen
		SDL_GL_SwapWindow( _sdlWindow );
	}
}

} // End of namespace BakedEngine
