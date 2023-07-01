#pragma once

// C++ Libraries
#include <string>
#include <vector>
#include <optional>

// SDL Libraries
#include <SDL.h>

// Vulkan Includes
#include <vulkan/vulkan_core.h>

namespace BakedEngine
{


const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef DEBUG
    const bool enableValidationLayers = true;
#else
    const bool enableValidationLayers = false;
#endif

extern VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
extern void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);



enum WindowFlags
{
	INVISIBLE = 0x1,
	FULLSCREEN = 0x2,
	BORDERLESS = 0x4
};

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

	bool isComplete() {
        return graphicsFamily.has_value() &&
			   presentFamily.has_value();
    }
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
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();

	std::vector<const char*> getRequiredExtensions();
	bool isDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);



	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	void setupDebugMessenger();
	bool checkValidationLayerSupport();
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);

	// SDL Program
	SDL_Window* _sdlWindow = nullptr;

	// Vulkan Instance
	VkInstance _instance;
	VkSurfaceKHR _surface;
	VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
	VkDevice _device;
	VkQueue _graphicsQueue;
	VkQueue _presentQueue;

	// Vulkan Debug
	VkDebugUtilsMessengerEXT debugMessenger;


	int _screenWidth;
	int _screenHeight;
};

} // End of namespace BakedEngine
