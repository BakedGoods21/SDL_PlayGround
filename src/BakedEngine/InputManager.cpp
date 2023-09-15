#include <BakedEngine/InputManager.h>

namespace BakedEngine
{

InputManager::InputManager() : m_mouseCoords(0.0f)
{

}

InputManager::~InputManager()
{

}

void InputManager::update()
{
	// Loop through keymap using a for each loop and copy it over to _previousKeyMap
	for (auto& it : m_keymap)
	{
		m_previousKeymap[it.first] = it.second;
	}
}

void InputManager::pressKey(unsigned int keyID)
{
	m_keymap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID)
{
	m_keymap[keyID] = false;
}

void InputManager::setMouseCoords(float x, float y)
{
	m_mouseCoords.x = x;
	m_mouseCoords.y = y;
}

bool InputManager::isKeyDown(unsigned int keyID)
{
	auto it = m_keymap.find(keyID);
	if (it != m_keymap.end())
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
	auto it = m_previousKeymap.find(keyID);
	if (it != m_previousKeymap.end())
	{
		return it->second;
	}
	else
	{
		return false;
	}
}

} // End of namespace BakedEngine
