// BakedEngine Includes
#include "BakedEngine/Window/Window.h"
#include "BakedEngine/SdlError.h"


namespace BakedEngine
{

VkShaderModule Window::createShaderModule(const std::vector<char>& code)
{
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	VkShaderModule shaderModule;
	if (vkCreateShaderModule(_device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Create Shader Module", "Failed to create shader module!");
	}

	return shaderModule;
}

void Window::createGraphicsPipeline()
{
	auto vertShaderCode = readFile("resources/Shaders/build/Vertex/SimpleTriangle.spv");
	auto fragShaderCode = readFile("resources/Shaders/build/Fragment/SimpleTriangle.spv");

	VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
	VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

	// VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
	// vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	// vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	// vertShaderStageInfo.module = vertShaderModule;
	// vertShaderStageInfo.pName = "main";

	// VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
	// fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	// fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	// fragShaderStageInfo.module = fragShaderModule;
	// fragShaderStageInfo.pName = "main";

	// VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

	vkDestroyShaderModule(_device, fragShaderModule, nullptr);
	vkDestroyShaderModule(_device, vertShaderModule, nullptr);
}

} // End of namespace BakedEngine
