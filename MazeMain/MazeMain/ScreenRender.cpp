#include "ScreenRender.h"

void GameBoard::ScreenInit()
{
	CONSOLE_CURSOR_INFO cci;
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void GameBoard::ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;
}
void GameBoard::ScreenClear()
{
	for (int i = 0; i < Map_size; i++)
	{
		COORD Coor = { i, 0 };
		DWORD dw;
		FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 80, Coor, &dw);
	}
}

void GameBoard::ScreenRelease()
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}

void GameBoard::ScreenPrint(int x, int y, std::string s)
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], s.c_str(), s.size(), &dw, NULL);
}
void GameBoard::Render() 
{
	ScreenClear();
	std::string s =func();
	ScreenPrint(0, 0, s);
	ScreenFlipping();
}