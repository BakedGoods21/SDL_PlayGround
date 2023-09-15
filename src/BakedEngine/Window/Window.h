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

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef DEBUG
    const bool enableValidationLayers = true;
#else
    const bool enableValidationLayers = false;
#endif

extern VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
extern void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT m_debugMessenger, const VkAllocationCallbacks* pAllocator);



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

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};



class Window
{
public:
	Window();
	~Window();

	bool create(std::string windowName, int screenWidth, int screenHeight, uint32_t currentFlags);

	void swapBuffer();
	void drawFrame();

	int getScreenWidth() { return m_screenWidth; }
	int getScreenHeight() { return m_screenHeight; }

	// Semaphores and Fences
	VkSemaphore m_imageAvailableSemaphore;
	VkSemaphore m_renderFinishedSemaphore;
	VkFence m_inFlightFence;

private:

	bool initSdl(std::string windowName, int screenWidth, int screenHeight, uint32_t currentFlags);

	bool initVulkan();
	void createInstance();
	void createSwapChain();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createImageViews();
	void createRenderPass();
	void createGraphicsPipeline();
	void createFrameBuffers();
	void createCommandPool();
	void createCommandBuffer();
	void createSyncObjects();

	std::vector<const char*> getRequiredExtensions();
	bool isDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	// File Loader function TODO: Put into it's own class
	std::vector<char> readFile(const std::string& filename);

	// Helper function TODO: Move somewhere
	VkShaderModule createShaderModule(const std::vector<char>& code);


	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	void setupDebugMessenger();
	bool checkValidationLayerSupport();
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);

	// Record command buffer
	void recordCommandBuffer(VkCommandBuffer m_commandBuffer, uint32_t imageIndex);

	// SDL Program
	SDL_Window* m_sdlWindow = nullptr;

	// Vulkan Instance
	VkInstance m_instance;
	VkSurfaceKHR m_surface;
	VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
	VkDevice m_device;
	VkQueue m_graphicsQueue;
	VkQueue m_presentQueue;
	VkSwapchainKHR m_swapChain;
	std::vector<VkImage> m_swapChainImages;
	VkFormat m_swapChainImageFormat;
	VkExtent2D m_swapChainExtent;

	// Image Views
	std::vector<VkImageView> m_swapChainImageViews;

	// Vulkan Debug
	VkDebugUtilsMessengerEXT m_debugMessenger;

	// Shader Pipeline?
	VkRenderPass m_renderPass;
	VkPipelineLayout m_pipelineLayout;
	VkPipeline m_graphicsPipeline;

	// Frame Buffer
	std::vector<VkFramebuffer> m_swapChainFramebuffers;

	// Command Pools
	VkCommandPool m_commandPool;
	VkCommandBuffer m_commandBuffer;

	int m_screenWidth;
	int m_screenHeight;
};

} // End of namespace BakedEngine
