#include <windows.h>

// SDL Libraries
#include <SDL.h>

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


	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Test" , "This is a test Window using SDL2", nullptr);

	return 0;
}
