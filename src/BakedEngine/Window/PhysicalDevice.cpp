// C++ Includes
#include <set>

// Local Includes
#include "BakedEngine/Window/Window.h"
#include "BakedEngine/SdlError.h"

namespace BakedEngine
{


void Window::pickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

	if (deviceCount == 0)
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Vulkan Initialization Error",  "Failed to find GPUs with Vulcan support!");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

	for (const auto& device : devices)
	{
		if (isDeviceSuitable(device))
		{
			m_physicalDevice = device;
			break;
		}
	}

	if (m_physicalDevice == VK_NULL_HANDLE)
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

	bool extensionsSupported = checkDeviceExtensionSupport(device);bool swapChainAdequate = false;

	if (extensionsSupported)
	{
		SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}

	return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

bool Window::checkDeviceExtensionSupport(VkPhysicalDevice device)
{
	uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "Extension Support",  "Extensions:");
    for (const auto& extension : availableExtensions)
	{
		//CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION, "",  extension.extensionName);
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}

} // End of namespace BakedEngine
