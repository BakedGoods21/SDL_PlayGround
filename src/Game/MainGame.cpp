// SDL Libraries
#include <SDL.h>

// BakedEngine Libraries
#include "BakedEngine/BakedEngine.h"
#include "BakedEngine/SdlError.h"
#include "BakedEngine/Vertex.h"

// Game Libraries
#include "Game/MainGame.h"

MainGame::MainGame()
{
	if (!BakedEngine::init())
	{
		BakedEngine::CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Main Game Init", "Could not initialize SDL", nullptr);
	}

	gameWindow.create("Test Window", 480, 480, 0);
}

void MainGame::run()
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Test" , "This is a test Window using SDL2", nullptr);
}
