// Windows Libraries
#include <windows.h>

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
int main()
{
#endif

	MainGame mainGame;

	mainGame.run();

	return 0;
}
