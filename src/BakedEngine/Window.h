#pragma once

// C++ Libraries
#include <string>
#include <vector>

// SDL Libraries
#include <SDL.h>

// Vulkan Includes
#include <vulkan/vulkan_core.h>

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
	bool initVulkan();
	void createInstance();
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	void setupDebugMessenger();
	bool checkValidationLayerSupport();
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);
	std::vector<const char*> getRequiredExtensions();

	// SDL Program
	SDL_Window* _sdlWindow = nullptr;

	// Vulkan Instance
	VkInstance _instance;
	VkDebugUtilsMessengerEXT debugMessenger;

	int _screenWidth;
	int _screenHeight;
};

} // End of namespace BakedEngine
