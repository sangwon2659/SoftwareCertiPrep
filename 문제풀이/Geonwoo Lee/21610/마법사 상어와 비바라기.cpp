#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<math.h>
#include<deque>

using namespace std;

int main()
{
	ifstream txt_input("input.txt");
	int n, m;

	txt_input >> n >> m;

	vector<vector<int>> map;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			txt_input >> map[i][j];
		}
	}


	vector<pair<int,int>> cloud; //구름 좌표 입력
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i >= n - 2 && i <= n - 1 && j >= 0 && j <= 1)
			{
				cloud.push_back({i,j});
			}
		}
	}
	vector<int> movingdir(m);
	vector<int> movinglen(m);

	vector<pair<int, int>> moveco;
	for (int i = 0; i < m; i++)		// s, d 좌표 입력
	{
		txt_input >> movingdir[i] >> movinglen[i];
		moveco.push_back({ movingdir[i] ,movinglen[i] });
	}

	int dx[] = { -1,-1,0,1,1,1,0,-1 };
	int dy[] = { 0,-1,-1,-1,0,1,1,1 };

	deque<pair<int, int>> new_cloud;
	int cnt = 0;

	for (int i = 0; i < m; i++)	//구름 이동
	{
		cloud[i].first += (moveco[i].second * dx[moveco[i].first] % n);
		cloud[i].second += (moveco[i].second * dy[moveco[i].first] % n);

		for (int j = 0; j < 4; j++)
		{

			map[cloud[j].first][cloud[j].second] ++; //비 1추가

			int cross[4] = { map[cloud[j].first - 1][cloud[j].second - 1],map[cloud[j].first - 1][cloud[j].second + 1],map[cloud[j].first + 1][cloud[j].second - 1],map[cloud[j].first + 1][cloud[j].second + 1] };
			//leftup, leftdown, rightup, rightdown
			if(cloud[j].first - 1>=0&& cloud[j].second - 1<n)

			if (cross[j] != 0)
				cnt++;

		}


	}

		

}
