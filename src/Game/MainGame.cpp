// C++ Includes
#include <iostream>

// SDL Libraries
#include <SDL.h>

// BakedEngine Libraries
#include "BakedEngine/BakedEngine.h"
#include "BakedEngine/SdlError.h"

// Game Libraries
#include "Game/MainGame.h"

MainGame::MainGame()
{
	if (!BakedEngine::init())
	{
		BakedEngine::CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Main Game Init", "Could not initialize SDL", nullptr);
	}

	if (!gameWindow.create("Test Window", 480, 480, 0))
	{
		BakedEngine::CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Main Game Init", "Could not initialize gameWindow", nullptr);
	}

	isRunning = true;
}

void MainGame::run()
{
	while (isRunning)
	{
		m_inputManager.update();

		SDL_Event evnt;
		while (SDL_PollEvent(&evnt))
		{
			switch (evnt.type)
			{
				case SDL_QUIT:
					isRunning = false;
					// std::cerr << "SDLQuit" << std::endl;
					break;
				case SDL_KEYDOWN:
					m_inputManager.pressKey(evnt.key.keysym.sym);
					// std::cerr << "KeyDown: " << evnt.key.keysym.sym << std::endl;
					break;
				case SDL_KEYUP:
					m_inputManager.releaseKey(evnt.key.keysym.sym);
					// std::cerr << "KeyUp: " << evnt.key.keysym.sym << std::endl;
					break;
				case SDL_MOUSEBUTTONDOWN:
					m_inputManager.pressKey(evnt.button.button);
					// std::cerr << "MouseButtonDown: " << evnt.key.keysym.sym << std::endl;
					break;
				case SDL_MOUSEBUTTONUP:
					m_inputManager.releaseKey(evnt.button.button);
					// std::cerr << "MouseButtonUP: " << evnt.key.keysym.sym << std::endl;
					break;
				case SDL_MOUSEMOTION:
					m_inputManager.setMouseCoords((float)evnt.motion.x, (float)480 - (float)evnt.motion.y);
					// std::cerr << "Mouse Movement: (" << evnt.motion.x << "," << evnt.motion.y << ")" << std::endl;
					break;
			}
		}
	}

	// SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Test" , "This is a test Window using SDL2", nullptr);
}

void MainGame::stop()
{
	isRunning = false;
}
