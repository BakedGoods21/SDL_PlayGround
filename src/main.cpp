// C++ Includes
#include <iostream>

// Windows Libraries
#include <windows.h>

// BakedEngine Libraries
#include "BakedEngine/SdlError.h"

// Main Game Libraries
#include "Game/MainGame.h"

#ifdef WINDOWS
int CALLBACK WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine,
					 int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);
#endif

#ifdef LINUX
int main(int argc, char** argv)
{
	if (argc != 1)
	{
		BakedEngine::CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Main Error", std::to_string(argc) + " invalid args: " + argv[0], nullptr);
		return EXIT_FAILURE;
	}
#endif

    try {
		MainGame mainGame;
		mainGame.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}
