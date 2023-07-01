// C++ Includes
#include <set>

// BakedEngine Includes
#include "BakedEngine/Window/Window.h"
#include "BakedEngine/SdlError.h"

// SDL Includes
#include <SDL_vulkan.h>

// Vulkan Includes
// #include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

namespace BakedEngine
{


bool Window::initVulkan()
{
    createInstance();
    setupDebugMessenger();
	createSurface();
	pickPhysicalDevice();
	createLogicalDevice();



	return true;
}

void Window::createInstance()
{
	if (enableValidationLayers && !checkValidationLayerSupport())
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "Vulkan Validation Layer Error",  "Validation layers requested, but not available!");
    }



//----------------------------------------------------------------------
// ---------------- Printing available extensions ----------------------
// ---------------------------------------------------------------------
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "Hardware extensions", "Available extensions:");

	for (const auto& extension : extensions)
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "", "\t" + std::string(extension.extensionName));
	}
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------



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
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Vulkan Initialization Error",  "Failed to create instance!");
	}
}

void Window::createSurface()
{
	if (!SDL_Vulkan_CreateSurface(_sdlWindow, _instance, &_surface))
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Vulkan Initialization Error",  "Failed to create Window Surface!");
	}
}

void Window::pickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(_instance, &deviceCount, nullptr);

	if (deviceCount == 0)
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Vulkan Initialization Error",  "Failed to find GPUs with Vulcan support!");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(_instance, &deviceCount, devices.data());

	for (const auto& device : devices)
	{
		if (isDeviceSuitable(device))
		{
			_physicalDevice = device;
			break;
		}
	}

	if (_physicalDevice == VK_NULL_HANDLE)
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Vulkan Initialization Error",  "Failed to find a suitable GPU!");
	}
}

bool Window::isDeviceSuitable(VkPhysicalDevice device)
{
    QueueFamilyIndices indices = findQueueFamilies(device);

	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);

	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);



//----------------------------------------------------------------------
// ---------------- Printing Device Properties -------------------------
// ---------------------------------------------------------------------
	CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "Device Info",  "Properties:");
	CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "",  "\tApi Version: " + std::to_string(deviceProperties.apiVersion));
	CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "",  "\tDevice Id: " + std::to_string(deviceProperties.deviceID));
	CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "",  "\tDevice Name: " + std::string(deviceProperties.deviceName));
	CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "",  "\tDevice Type: " + std::to_string(deviceProperties.deviceType));
	CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "",  "\tDriver Version: " + std::to_string(deviceProperties.driverVersion));
	CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "",  "\tColor Sample Counts: " + std::to_string(deviceProperties.limits.framebufferColorSampleCounts));
	CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "",  "\tColor Depth Counts: " + std::to_string(deviceProperties.limits.framebufferDepthSampleCounts));
	CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "",  "\tMax Shared Mem Size: " + std::to_string(deviceProperties.limits.maxComputeSharedMemorySize));
	CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "",  "\tVendor Id: " + std::to_string(deviceProperties.vendorID));
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

//----------------------------------------------------------------------
// ---------------- Printing Device Features ---------------------------
// ---------------------------------------------------------------------
	CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "Device Info",  "Features: Too many to manually print");
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------



	return indices.isComplete();
}

QueueFamilyIndices Window::findQueueFamilies(VkPhysicalDevice device)
{
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "Family Queues",  "Queues with VK_QUEUE_GRAPHICS_BIT");
	for (unsigned int i = 0; i < queueFamilies.size(); i++)
	{
		const auto& queueFamily = queueFamilies[i];

		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "",  "\t" + std::to_string(i));
			indices.graphicsFamily = i;
		}

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, _surface, &presentSupport);

		if (presentSupport)
		{
			indices.presentFamily = i;
		}

		// Comment out to print all queues with graphics families
		if (indices.isComplete()) {
			break;
		}
	}

	return indices;
}

void Window::createLogicalDevice()
{
	QueueFamilyIndices indices = findQueueFamilies(_physicalDevice);

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	// VkDeviceQueueCreateInfo queueCreateInfo{};
	// queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	// queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
	// queueCreateInfo.queueCount = 1;

	// float queuePriority = 1.0f;
	// queueCreateInfo.pQueuePriorities = &queuePriority;

	VkPhysicalDeviceFeatures deviceFeatures{};

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();

	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = 0;

	if (enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(_physicalDevice, &createInfo, nullptr, &_device) != VK_SUCCESS)
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "Vulkan Initialization Error",  "Failed to create logical device!");
	}
	vkGetDeviceQueue(_device, indices.graphicsFamily.value(), 0, &_graphicsQueue);
	vkGetDeviceQueue(_device, indices.presentFamily.value(), 0, &_presentQueue);
}

std::vector<const char*> Window::getRequiredExtensions()
{
	uint32_t sdlExtensionCount = 0;

	if (!SDL_Vulkan_GetInstanceExtensions(_sdlWindow, &sdlExtensionCount, nullptr))
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "SDL Vulkan Initialization Error",  "Failed to get instance extension count!");
	}


	std::vector<const char *> sdlExtensions(sdlExtensionCount);

	if (!SDL_Vulkan_GetInstanceExtensions(_sdlWindow, &sdlExtensionCount, sdlExtensions.data()))
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "SDL Vulkan Initialization Error",  "Failed to get instance extensions!");
	}

	if (enableValidationLayers)
	{
		sdlExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return sdlExtensions;
}

} // End of namespace BakedEngine
