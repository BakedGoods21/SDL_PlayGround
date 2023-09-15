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

	bool isRunning = false;

	BakedEngine::Window gameWindow;

	// Input Manager
	BakedEngine::InputManager m_inputManager;
};
