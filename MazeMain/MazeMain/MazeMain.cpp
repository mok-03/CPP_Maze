#include <unordered_map>
#include <map>
#include <string>
#include <queue>
#include <algorithm>
#include<Math.h>
#include <iostream>
#include "maze.h"
#include <functional>
#include <conio.h>
#include <windows.h>
#include "ScreenRender.h"

using namespace std;
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
class MazeMain
{
public:
	Mazemap	map;
	GameBoard GameRender;

	void init();

	void a_main();

	string Render();

	void Update();

	~MazeMain();
	bool Game = true;
private:

};

int main() {

	MazeMain m;
	m.init();
	m.a_main();
}


void MazeMain::init()
{
	map.init();

	GameRender.Map_size = map.MapSizeLW;
	GameRender.ScreenInit();

	GameRender.func = [this]() {
		return Render();
	};

}

void MazeMain::a_main()
{
	while (Game)
	{
		while (_kbhit() == 0) {
			GameRender.Render();
			Update();
		}
	}

}

string MazeMain::Render()
{

	string s;

	//map.PlayerPos[0] map.PlayerPos[1]
	for (int i = 0; i < map.Map.size(); i++)
	{
		for (int j = 0; j < map.Map[i].size(); j++)
		{

			if (map.PlayerPos[0] == i && map.PlayerPos[1] == j) {
				s += map.MapStateChar[2];
				continue;
			}
			if (
				map.PlayerPos[0] + map.PlayerEyesight > i &&
				map.PlayerPos[0] - map.PlayerEyesight < i &&
				map.PlayerPos[1] + map.PlayerEyesight > j &&
				map.PlayerPos[1] - map.PlayerEyesight < j
				) {
				//s += map.MapStateChar[map.Map[i][j]];
			}
			else {
				//s += map.MapStateChar[Mazemap::MapState::wall];

			}
			s += map.MapStateChar[map.Map[i][j]];

		}
		s += "\n";
	}
	return s;

}

void MazeMain::Update()
{
	int keyInput;
	keyInput = _getch();
	if (keyInput == 224) {
		keyInput = _getch();
	}
	if (keyInput == 115 || keyInput == 80) {
		map.PlayerMove(Mazemap::PlayerMoverDirection::UP);
	}
	if (keyInput == 97 || keyInput == 75) {
		map.PlayerMove(Mazemap::PlayerMoverDirection::LEFT);
	}
	if (keyInput == 100 || keyInput == 77) {
		map.PlayerMove(Mazemap::PlayerMoverDirection::RIGHT);
	}
	if (keyInput == 119 || keyInput == 72) {
		map.PlayerMove(Mazemap::PlayerMoverDirection::DOWN);
	}

	if (keyInput == 'r' || keyInput == 'R') {
		map.MapRestart();
	}
}

MazeMain::~MazeMain()
{

}
