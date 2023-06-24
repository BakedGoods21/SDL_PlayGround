#pragma once

#include <map>
#include <string>

#include <BakedEngine/GLTexture.h>

namespace BakedEngine
{

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	GLTexture getTexture(std::string texturePath);

private:
	std::map<std::string, GLTexture> _textureMap;
};

} // End of namespace BakedEngine
