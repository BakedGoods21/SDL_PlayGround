#pragma once

#include <string>

#include <BakedEngine/TextureCache.h>

namespace BakedEngine
{

class ResourceManager
{
public:
	static GLTexture getTexture(std::string texturePath);

private:
	static TextureCache _textureCache;
};

} // End of namespace BakedEngine
