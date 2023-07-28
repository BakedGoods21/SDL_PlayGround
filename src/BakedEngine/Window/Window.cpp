// BakedEngine Includes
#include "BakedEngine/Window/Window.h"
#include "BakedEngine/SdlError.h"

namespace BakedEngine
{


Window::Window() {}

Window::~Window()
{
	for (auto imageView : swapChainImageViews)
	{
		vkDestroyImageView(_device, imageView, nullptr);
	}

	vkDestroySwapchainKHR(_device, _swapChain, nullptr);
	vkDestroyDevice(_device, nullptr);

    if (enableValidationLayers) {
        DestroyDebugUtilsMessengerEXT(_instance, debugMessenger, nullptr);
    }

	vkDestroySurfaceKHR(_instance, _surface, nullptr);
    vkDestroyInstance(_instance, nullptr);

	// Destroy window
	if (_sdlWindow)
	{
		SDL_DestroyWindow( _sdlWindow );
	}

	SDL_Quit();
}

bool Window::create(std::string windowName, int screenWidth, int screenHeight, uint32_t currentFlags)
{
	bool status = initSdl(windowName, screenWidth, screenHeight, currentFlags);
	if (status) { status = initVulkan(); }

	return status;
}

bool Window::initSdl(std::string windowName, int screenWidth, int screenHeight, uint32_t currentFlags)
{
	uint32_t flags = SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN;

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


} // End of namespace BakedEngine
