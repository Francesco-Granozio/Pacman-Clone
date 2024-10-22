#include "GameManager.h"
#include <Windows.h>

int main()
{
	GameManager gameManager;
#ifdef NDEBUG
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);
#endif

	gameManager.StartGameManager();

	gameManager.Update();

	return 0;
}
