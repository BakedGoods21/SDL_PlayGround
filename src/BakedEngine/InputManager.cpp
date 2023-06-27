#include <BakedEngine/InputManager.h>

namespace BakedEngine
{

InputManager::InputManager() : _mouseCoords(0.0f)
{

}

InputManager::~InputManager()
{

}

void InputManager::update()
{
	// Loop through keymap using a for each loop and copy it over to _previousKeyMap
	for (auto& it : _keymap)
	{
		_previousKeymap[it.first] = it.second;
	}
}

void InputManager::pressKey(unsigned int keyID)
{
	_keymap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID)
{
	_keymap[keyID] = false;
}

void InputManager::setMouseCoords(float x, float y)
{
	_mouseCoords.x = x;
	_mouseCoords.y = y;
}

bool InputManager::isKeyDown(unsigned int keyID)
{
	auto it = _keymap.find(keyID);
	if (it != _keymap.end())
	{
		return it->second;
	}
	else
	{
		return false;
	}
}

// Returns true if if the key was just pressed
bool InputManager::isKeyPressed(unsigned int keyID)
{
	if (isKeyDown(keyID) == true && wasKeyPressed(keyID) == false)
	{
		return true;
	}

	return false;
}

// Returns true if if the key was just pressed
bool InputManager::wasKeyPressed(unsigned int keyID)
{
	auto it = _previousKeymap.find(keyID);
	if (it != _previousKeymap.end())
	{
		return it->second;
	}
	else
	{
		return false;
	}
}

} // End of namespace BakedEngine
