#include <BakedEngine/TextureCache.h>
#include <BakedEngine/ImageLoader.h>

namespace BakedEngine
{

TextureCache::TextureCache() { }

TextureCache::~TextureCache() { }

GLTexture TextureCache::getTexture(std::string texturePath)
{
	// Lookup the texture and see if its in the map
	std::map<std::string, GLTexture>::iterator mit = _textureMap.find(texturePath);

	// Check if its not in the map
	if (mit == _textureMap.end())
	{
		GLTexture newTexture = ImageLoader::loadPNG(texturePath);

		std::pair<std::string, GLTexture> newPair(texturePath, newTexture);

		// Insert it into the map
		_textureMap.insert(newPair);

		return newTexture;
	}

	return mit->second;
}

} // End of namespace BakedEngine
