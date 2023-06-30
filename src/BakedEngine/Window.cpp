// C++ Includes
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <sstream>

// SDL Includes
#include <SDL_vulkan.h>

// Vulkan Includes
// #include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

// BakedEngine Includes
#include "BakedEngine/Window.h"
#include "BakedEngine/SdlError.h"

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

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr)
	{
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }
	else
	{
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
 {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr)
	{
        func(instance, debugMessenger, pAllocator);
    }
}





Window::Window() {}

Window::~Window()
{
    if (enableValidationLayers) {
        DestroyDebugUtilsMessengerEXT(_instance, debugMessenger, nullptr);
    }

    vkDestroyInstance(_instance, nullptr);

	// Destroy window
	if (_sdlWindow)
	{
		SDL_DestroyWindow( _sdlWindow );
	}
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

bool Window::initVulkan()
{
    // uint32_t extensionCount = 0;
    // vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	// CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "Vulkan Info",  "Extension Count: " + std::to_string(extensionCount));

    createInstance();
    setupDebugMessenger();



	return true;
}

void Window::createInstance()
{
	if (enableValidationLayers && !checkValidationLayerSupport())
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "Vulkan Validation Layer Error",  "Validation layers requested, but not available!");
    }
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	auto sdlExtensions = getRequiredExtensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(sdlExtensions.size());
	createInfo.ppEnabledExtensionNames = sdlExtensions.data();

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};

	if (enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();

		populateDebugMessengerCreateInfo(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
	}
	else
	{
		createInfo.enabledLayerCount = 0;

        createInfo.pNext = nullptr;
	}

	if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS)
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Vulkan Initialization Error",  "Could not create instance!");
	}
}

void Window::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
	createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = debugCallback;
}

void Window::setupDebugMessenger()
{
	if (!enableValidationLayers)
	{
		return;
	}

	VkDebugUtilsMessengerCreateInfoEXT createInfo;
	populateDebugMessengerCreateInfo(createInfo);

	if (CreateDebugUtilsMessengerEXT(_instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Vulkan Debug Messenger",  "Failed to set up debug messenger!");
	}
}

bool Window::checkValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers)
	{
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound)
		{
			return false;
		}
	}

	return true;
}

VKAPI_ATTR VkBool32 VKAPI_CALL Window::debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData)
{
	std::ostringstream address;
	address << pUserData;
	std::string addressstr = address.str();

	SDL_MessageBoxFlags sdlSeverityFlag = SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION;

	switch(messageSeverity)
	{
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			sdlSeverityFlag = SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION;
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			sdlSeverityFlag = SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION;
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			sdlSeverityFlag = SDL_MessageBoxFlags::SDL_MESSAGEBOX_WARNING;
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			sdlSeverityFlag = SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR;
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT:
			break;
	}

	CustomSdlError::DisplayError(sdlSeverityFlag, "Vulkan Validation Layer Error\n",  std::string(pCallbackData->pMessage) +
					"\nType: " + std::to_string(messageType) +
					"\npCallbackData message: " + pCallbackData->pMessage +
				//  "\npCallbackData pObects: " + pCallbackData->pObjects +
					"\npCallbackData objectCount: " + std::to_string(pCallbackData->objectCount) +
					"\npUserData: " + addressstr);

    return VK_FALSE;
}

std::vector<const char*> Window::getRequiredExtensions()
{
	uint32_t sdlExtensionCount = 0;
	const char** sdlExtensions = (const char**)malloc(sizeof(char*) * sdlExtensionCount);

	SDL_Vulkan_GetInstanceExtensions(_sdlWindow, &sdlExtensionCount, sdlExtensions);

	std::vector<const char*> extensions(sdlExtensions, sdlExtensions + sdlExtensionCount);

	if (enableValidationLayers)
	{
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}

} // End of namespace BakedEngine
