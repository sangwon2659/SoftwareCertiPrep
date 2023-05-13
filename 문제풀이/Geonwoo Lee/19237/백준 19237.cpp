#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<math.h>

using namespace std;

class Shark
{
public:
	int x, y;
	int Dir;
	bool Live=1;
	
	int cnt(int k);
	int smell(int k);
	int move();
	int priority[4][4];
};
int Shark::cnt(int k)
{

	return k--;
}
int Shark::move()
{
	return 0;
}

int Shark::smell(int k)
{
	return k--;
}

int main()
{
	Shark shark[400];

	ifstream txt_input("input.txt");

	int n, m, k; // n: N*N 격자, m: M개의 상어, k: k번 이동 

	txt_input >> n >> m >> k;

	vector<vector<int>> base_map(n, vector<int>(n));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			txt_input >> base_map[i][j];
			if (base_map[i][j] != 0)	//상어 위치 입력
			{
				int& shark_num = base_map[i][j];
				shark[shark_num].x = j;
				shark[shark_num].y = i;
			}
			
		}
	}

	for (int i = 1; i <= m; i++)	//상어 방향
	{
		txt_input >> shark[i].Dir;
	}

	for (int i = 1; i <= m; i++)	//우선순위 입력
	{
		for (int j = 1; j <= 4; j++)
		{
			for (int p = 1; p <= 4; p++)
			{
				txt_input >> shark[i].priority[j][p];
				cout << shark[i].priority[j][p];
			}
		}
	}

	int num = 1;

	for (int i = 1; i <= m; i++)
	{
		int& north = base_map[shark[i].x][shark[i].y-1];
		int& west = base_map[shark[i].x - 1][shark[i].y];
		int& east = base_map[shark[i].x + 1][shark[i].y];
		int& south = base_map[shark[i].x][shark[i].y + 1];

		if (north == 0 || west == 0 || east == 0 || south == 0)
		{
			if (shark[i].Dir == 1)//위
			{
				shark[i].priority[1][1]
			}
			else if (shark[i].Dir == 2)//아래
			{

			}
			else if (shark[i].Dir == 3)//왼
			{

			}
			else if (shark[i].Dir == 4)//오
			{

			}
		}
		else
		{

		}
	}
}
