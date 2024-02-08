#include"maze.h"
#include<windows.h>
#include <vector>
#include <functional>
#include "renderFunc.h"



void Mazemap::init()
{
	RandomMapPoint = uniform_int_distribution<int>(0, 3);
	mt = mt19937_64(rd());
	AutomaticMapMaker(MapSizeLW);

}

void Mazemap::PlayerMove(PlayerMoverDirection m)
{
	int IF_PlayerPos[2] = { PlayerPos[0] + MoverDirection[m][0],PlayerPos[1] + MoverDirection[m][1] };

	if ((IF_PlayerPos[0] >= 0 && IF_PlayerPos[0] < MapSizeLW) &&
		(IF_PlayerPos[1] >= 0 && IF_PlayerPos[1] < MapSizeLW) &&
		!(Map[IF_PlayerPos[0]][IF_PlayerPos[1]] == Mazemap::MapState::wall))
	{
		std::copy(std::begin(IF_PlayerPos), std::end(IF_PlayerPos), std::begin(PlayerPos));
	}
}

void Mazemap::MapRestart()
{
	Map.clear();
	AutomaticMapMaker(MapSizeLW);
}

void Mazemap::AutomaticMapMaker(int MapSize)
{
	uniform_int_distribution<int> Maprange(0, MapSize-1);
	int  P_x, P_y, EndP_x, EndP_y = 0;

	if (SpareEndPoint.size() > 0) SpareEndPoint.clear();

	P_x = Maprange(mt);
	P_y = Maprange(mt);

	PlayerPos[0] = P_x;
	PlayerPos[1] = P_y;

	//end 위치 찾기

		//while (true)
	//{
	//	EndP_x = Maprange(mt);
	//	EndP_y = Maprange(mt);

	//	if (EndP_x < (P_x - Sp_Ep_MDistance) || EndP_x >(P_x + Sp_Ep_MDistance) &&
	//		EndP_y < (P_y - Sp_Ep_MDistance) || EndP_y >(P_y + Sp_Ep_MDistance)
	//		)break;
	//}

	for (int i = 0; i < MapSize; i++) {
		Map.push_back(std::vector<int>());
		for (int j = 0; j < MapSize; j++) {
			Map[i].push_back(1);
		}
	}
	Map[P_x][P_y] = MapState::startPoint;
	//Map[EndP_x][EndP_y] =MapState::EndPoint;
	ProceduralGeneration(P_x, P_y);
	
	int randPoint = Maprange(mt) % (SpareEndPoint.size() - 1);

		Map[SpareEndPoint[randPoint][0]][SpareEndPoint[randPoint][1]] = MapState::EndPoint;

	IsGenerateMap = true;
}

void Mazemap::ProceduralGeneration(int generatex, int generatey, PlayerMoverDirection goback)
{
	//현재위치 길로 바꿔주기

	if (Map[generatex][generatey] == MapState::wall){
		Map[generatex - (MoverDirection[goback][0])][generatey - MoverDirection[goback][1]] = MapState::road;
		Map[generatex][generatey] = MapState::road;
	}

	else if (Map[generatex][generatey] == MapState::road) 
	{

		
		return;
	}


	////갈수있는 방향 받기
	////같던길 제외 해주기
	auto nextRoad = canDoitGeneration(generatex, generatey, goback);
	////섞기
	for (int i = 0; i < nextRoad.size(); i++) {
		int a = RandomMapPoint(mt) % nextRoad.size();
		if (a == i)continue;
		PlayerMoverDirection m = nextRoad[i];
		nextRoad[i] = nextRoad[a];
		nextRoad[a] = m;
	}

	if (!(nextRoad.size() > 0)) {
		SpareEndPoint.push_back({ generatex, generatey });
	}

	for (int i = 0; i < nextRoad.size(); i++) {
		ProceduralGeneration(generatex + MoverDirection[nextRoad[i]][0] * 2, generatey + MoverDirection[nextRoad[i]][1] * 2, nextRoad[i]);
	}
}

std::vector<Mazemap::PlayerMoverDirection> Mazemap::canDoitGeneration(int x, int y, PlayerMoverDirection goback)
{
	std::vector<PlayerMoverDirection> v;

	if (x + 2 < MapSizeLW && Map[x + 2][y] == Mazemap::MapState::wall &&
		Map[x + 1][y] == Mazemap::MapState::wall &&
		goback != DOWN)v.push_back(UP);
	if (x - 2 >= 0 && Map[x - 2][y] == Mazemap::MapState::wall &&
		Map[x - 1][y] == Mazemap::MapState::wall &&
		goback != UP)v.push_back(DOWN);
	if (y + 2 < MapSizeLW && Map[x][y + 2] == Mazemap::MapState::wall &&
		Map[x][y +1] == Mazemap::MapState::wall &&
		goback != LEFT)v.push_back(RIGHT);
	if (y - 2 >= 0 && Map[x][y - 2] == Mazemap::MapState::wall &&
		Map[x][y - 1] == Mazemap::MapState::wall &&
		goback != RIGHT)v.push_back(LEFT);
	return v;
}
