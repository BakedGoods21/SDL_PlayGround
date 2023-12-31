// C++ Libraries
#include <stdlib.h>

// BakedEngine Libraries
#include "BakedEngine/SdlError.h"

namespace BakedEngine
{

void CustomSdlError::DisplayError(SDL_MessageBoxFlags messageType, std::string title, std::string message, SDL_Window *window)
{
	if (messageType != SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION)
	{
		SDL_ShowSimpleMessageBox(messageType, title.c_str(), message.c_str(), window);
	}

	if (messageType == SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR)
	{
		exit(EXIT_FAILURE);
	}
}

} // End of namespace BakedEngine
