#pragma once

// C++ Libraries
#include <string>

// SDL Libraries
#include <SDL.h>

namespace BakedEngine
{

class CustomSdlError
{
public:
	CustomSdlError() = default;
	~CustomSdlError() = default;

	static void DisplayError(SDL_MessageBoxFlags messageType, std::string title, std::string message, SDL_Window *window = NULL);
};

} // End of namespace BakedEngine
