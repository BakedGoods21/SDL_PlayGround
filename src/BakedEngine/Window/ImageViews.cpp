// C++ Includes
// #include <algorithm> // Necessary for std::clamp
// #include <limits> // Necessary for std::numeric_limits

// SDL Includes
#include <SDL_vulkan.h>

// Local Includes
#include "BakedEngine/Window/Window.h"
#include "BakedEngine/SdlError.h"

namespace BakedEngine
{

void Window::createImageViews()
{
	swapChainImageViews.resize(swapChainImages.size());

	for (size_t i = 0; i < swapChainImages.size(); i++)
	{
		VkImageViewCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = swapChainImages[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = swapChainImageFormat;

		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;
		if (vkCreateImageView(_device, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS)
		{
			CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Vulkan Image Creation Initialization Error",  "Failed to create image views!");
		}
	}



}

} // End of namespace BakedEngine
