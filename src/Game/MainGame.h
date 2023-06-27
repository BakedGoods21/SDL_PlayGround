#pragma once

// BakedEngine Includes
#include "BakedEngine/Window.h"
#include "BakedEngine/GLSLProgram.h"
#include <BakedEngine/InputManager.h>

class MainGame
{
public:
	MainGame();
	~MainGame() = default;

	void run();
	void stop();

private:
	bool isRunning = false;

	BakedEngine::Window gameWindow;

	// GLSL Program
	BakedEngine::GLSLProgram m_colorShaderProgram;

	// Input Manager
	BakedEngine::InputManager m_inputManager;
};
