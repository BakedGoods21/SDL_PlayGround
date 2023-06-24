#include <BakedEngine/ResourceManager.h>

namespace BakedEngine
{

TextureCache ResourceManager::_textureCache;

GLTexture ResourceManager::getTexture(std::string texturePath)
{
	return _textureCache.getTexture(texturePath);
}

} // End of namespace BakedEngine
