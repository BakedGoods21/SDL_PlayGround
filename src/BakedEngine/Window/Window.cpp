// BakedEngine Includes
#include "BakedEngine/Window/Window.h"
#include "BakedEngine/SdlError.h"

namespace BakedEngine
{


Window::Window() {}

Window::~Window()
{
    vkDeviceWaitIdle(_device);

    vkDestroySemaphore(_device, imageAvailableSemaphore, nullptr);
    vkDestroySemaphore(_device, renderFinishedSemaphore, nullptr);
    vkDestroyFence(_device, inFlightFence, nullptr);

    vkDestroyCommandPool(_device, commandPool, nullptr);

    for (auto framebuffer : swapChainFramebuffers)
	{
        vkDestroyFramebuffer(_device, framebuffer, nullptr);
    }
    vkDestroyPipeline(_device, graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(_device, pipelineLayout, nullptr);
    vkDestroyRenderPass(_device, renderPass, nullptr);

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

void Window::drawFrame()
{
    uint32_t imageIndex;
    vkAcquireNextImageKHR(_device, _swapChain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

    vkWaitForFences(_device, 1, &inFlightFence, VK_TRUE, UINT64_MAX);
	vkResetFences(_device, 1, &inFlightFence);

	vkResetCommandBuffer(commandBuffer, 0);
	recordCommandBuffer(commandBuffer, imageIndex);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
	VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	VkSemaphore signalSemaphores[] = {renderFinishedSemaphore};
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	if (vkQueueSubmit(_graphicsQueue, 1, &submitInfo, inFlightFence) != VK_SUCCESS)
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Draw Frame Error",  "Failed to submit draw command buffer");
	}

	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = {_swapChain};
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;

	presentInfo.pResults = nullptr; // Optional

	vkQueuePresentKHR(_presentQueue, &presentInfo);
}


} // End of namespace BakedEngine
