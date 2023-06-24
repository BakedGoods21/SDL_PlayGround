#pragma once

#include <string>

#include <BakedEngine/GLTexture.h>

namespace BakedEngine
{

class ImageLoader
{
public:
	static GLTexture loadPNG(std::string filePath);
};

} // End of namespace BakedEngine
