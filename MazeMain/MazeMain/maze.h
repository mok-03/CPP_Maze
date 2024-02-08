#pragma once
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include<Math.h>
#include<random>
#include <queue>
#include <stack>
//https://codevang.tistory.com/39 ���߹��� �����
// �ϳ� �� ���� ��������°� ���� ( bfs �һ���
#define Pairxy  pair<int, int>
#define  MapLength_Widt = 25
using namespace std;

class  Mazemap
{

public:
	enum PlayerMoverDirection
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		MovendPointeEndPoint
	};
	enum MapState {
		road = 0,
		wall,
		startPoint,
		EndPoint
	};

	const char MapStateChar[4][4] = { "��","��","��","��" };

	int MapSizeLW = 25;
	int PlayerEyesight = 5;
	int PlayerPos[2] = { 0,0 };

	std::vector<std::vector<int>> Map{};

	void init();
	void PlayerMove(PlayerMoverDirection m);
	void MapRestart();


private:
	// �ʻ��� �Ϸ� Ȯ��
	bool IsGenerateMap = false;
	/// <summary>
	/// [4][2]  [1]�� [2]�� [3]�� [4]��
	/// </summary>
	const int MoverDirection[4][2] = { {1,0} ,{-1,0} ,{0,-1} ,{0,1} };

	//start point end point  ��  �Ÿ�����
	const int Sp_Ep_MDistance = 3;
	vector<vector<int>> SpareEndPoint;
	//���� ���� Ŭ����
	uniform_int_distribution<int> RandomMapPoint;
	random_device  rd;
	mt19937_64 mt;

	void AutomaticMapMaker(int MapSize);
	void ProceduralGeneration(int generatex, int generatey, PlayerMoverDirection goback = PlayerMoverDirection::MovendPointeEndPoint);

	std::vector<PlayerMoverDirection> canDoitGeneration(int x, int y, PlayerMoverDirection goback);
};