#include <fstream>

#include <BakedEngine/IOManager.h>
#include <BakedEngine/SdlError.h>

namespace BakedEngine
{

bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
{
	std::ifstream file(filePath, std::ios::binary);

	if (file.fail())
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "File Read", "Unable to open " + filePath);
		return false;
	}

	// Seek to the end
	file.seekg(0, std::ios::end);

	// Get file size
	int fileSize = (int)file.tellg();

	// Seek back to the beginning of the file
	file.seekg(0, std::ios::beg);

	// Subtract any header data
	fileSize -= (int)file.tellg();

	buffer.resize(fileSize);
	file.read((char *)buffer.data(), fileSize);

	file.close();

	return true;
}

} // End of namespace BakedEngine
