#pragma once
#include <WTypesbase.h>
#include <string>
#include <functional>
class GameBoard {

	int g_nScreenIndex;
	HANDLE g_hScreen[2];
	
public:
	int	Map_size;
	std::function<std::string()>  func;
	void ScreenInit();
	void ScreenFlipping();
	void ScreenClear();
	void ScreenRelease();
	void ScreenPrint(int x, int y, std::string s);
	void Render();
};