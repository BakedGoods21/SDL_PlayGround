#pragma once

// BakedEngine Includes
#include "BakedEngine/Window.h"
#include "BakedEngine/GLSLProgram.h"

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
};
