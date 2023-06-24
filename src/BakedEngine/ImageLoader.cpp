#include <BakedEngine/ImageLoader.h>
#include <BakedEngine/Picopng.h>
#include <BakedEngine/IOManager.h>
#include <BakedEngine/SdlError.h>

namespace BakedEngine
{

GLTexture ImageLoader::loadPNG(std::string filePath)
{
	GLTexture texture = {};

	std::vector<unsigned char> out;

	std::vector<unsigned char> in;
	unsigned long width, height;

	if (!IOManager::readFileToBuffer(filePath, in))
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Reading PNG Error", "Unable to read texture file: " + filePath);
		return GLTexture();
	}

	int errorCode = PICO_PNG::decodePNG(out, width, height, in.data(), in.size());
	if (errorCode != 0)
	{
		CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Reading PNG Error", "PicoPng failed with code: " + errorCode);
	}

	glGenTextures(1, &texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, out.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = width;
	texture.height = height;

	return texture;
}

} // End of namespace BakedEngine
