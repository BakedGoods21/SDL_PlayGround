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

	int getScreenWidth() { return _screenWidth; }
	int getScreenHeight() { return _screenHeight; }
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
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	// SDL Program
	SDL_Window* _sdlWindow = nullptr;

	// Vulkan Instance
	VkInstance _instance;
	VkSurfaceKHR _surface;
	VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
	VkDevice _device;
	VkQueue _graphicsQueue;
	VkQueue _presentQueue;
	VkSwapchainKHR _swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	// Image Views
	std::vector<VkImageView> swapChainImageViews;

	// Vulkan Debug
	VkDebugUtilsMessengerEXT debugMessenger;

	// Shader Pipeline?
	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	// Frame Buffer
	std::vector<VkFramebuffer> swapChainFramebuffers;

	// Command Pools
	VkCommandPool commandPool;
	VkCommandBuffer commandBuffer;


	int _screenWidth;
	int _screenHeight;
};

} // End of namespace BakedEngine
