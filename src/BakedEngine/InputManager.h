#pragma once

// C++ Includes
#include <unordered_map>

// GLM Includes
#include <glm/vec2.hpp>

namespace BakedEngine
{

class InputManager
{
public:
	InputManager();
	~InputManager();

	void update();

	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);

	void setMouseCoords(float x, float y);

	// Returns true if if the key is held down
	bool isKeyDown(unsigned int keyID);

	// Returns true if if the key was just pressed
	bool isKeyPressed(unsigned int keyID);

	// Getters
	glm::vec2 getMouseCoords() const { return _mouseCoords; }

private:
	std::unordered_map<unsigned int, bool> _keymap;
	std::unordered_map<unsigned int, bool> _previousKeymap;
	glm::vec2 _mouseCoords;

	bool wasKeyPressed(unsigned int keyID);

};

} // End of namespace BakedEngine