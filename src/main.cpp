// C++ Includes
#include <iostream>

// Windows Libraries
#include <windows.h>

// BakedEngine Libraries
#include "BakedEngine/SdlError.h"

// Main Game Libraries
#include "Game/MainGame.h"

int CALLBACK WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine,
					 int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

    try {
		MainGame mainGame;
		mainGame.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}
