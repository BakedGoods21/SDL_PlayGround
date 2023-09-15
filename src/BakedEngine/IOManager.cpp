#include <fstream>

#include <BakedEngine/IOManager.h>
#include <BakedEngine/SdlError.h>

namespace BakedEngine
{

bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
{
	// Open file at end in binary
	std::ifstream file(filePath, std::ios::ate | std::ios::binary);

	if (!file.is_open())
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "File Read", "Unable to open " + filePath);
		return false;
	}

	// Get file size
	int fileSize = (int)file.tellg();

	buffer.resize(fileSize);

	// Seek back to the beginning of the file
	file.seekg(0);

	// Read the contents of the file
	file.read((char *)buffer.data(), fileSize);

	// Close the file
	file.close();

	return true;
}

} // End of namespace BakedEngine
