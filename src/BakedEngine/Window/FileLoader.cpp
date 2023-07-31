// C++ Includes
#include <fstream>

// BakedEngine Includes
#include "BakedEngine/Window/Window.h"
#include "BakedEngine/SdlError.h"


namespace BakedEngine
{

std::vector<char> Window::readFile(const std::string& filename)
{
	// Attempt to open file in binary mode (std::ios::binary) start at the end of the file (std::ios::ate)
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	// Ensure File is open
    if (!file.is_open())
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "File Loaded Error", "Failed to load " + filename);
    }

	size_t fileSize = (size_t) file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;
}

} // End of namespace BakedEngine
