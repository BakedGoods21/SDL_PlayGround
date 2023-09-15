#pragma once

// BakedEngine Includes
#include "BakedEngine/Window/Window.h"
#include "BakedEngine/InputManager.h"

class MainGame
{
public:
	MainGame();
	~MainGame() = default;

	void run();
	void stop();

private:
	void pullEvents();

	bool m_isRunning = false;

	BakedEngine::Window m_gameWindow;

	// Input Manager
	BakedEngine::InputManager m_inputManager;
};
