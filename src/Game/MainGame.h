#pragma once

#include "BakedEngine/Window.h"

class MainGame
{
public:
	MainGame();
	~MainGame() = default;

	void run();

private:
	BakedEngine::Window gameWindow;
};
