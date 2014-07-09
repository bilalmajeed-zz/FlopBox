// Flappy Bird Clone
// By daloser247 aka Bilal Majeed

//Define the minimum operating system for the application:
#define _WIN32_WINNT _WIN32_WINNT_WINXP //Windows XP
//Get rid of the annoying min() and max() macros:
#define NOMINMAX
//Include the windows header:
#include <windows.h>

#include "Game.h"

int wWinMain(HINSTANCE hInst, HINSTANCE prevInst, LPWSTR szCmdLine, int nCmdShow)
{
	Game game;
	game.start();
	return 0;
}