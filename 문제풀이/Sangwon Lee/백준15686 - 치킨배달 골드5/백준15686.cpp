#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

struct Pos
{
	int r;
	int c;
};

int N, M;
int Grid[50][50];
vector<Pos> house;
vector<Pos> chicken_place;
int result = 1000;
bool included[10000];
vector<Pos> candidate;

int findCityDist(const vector<Pos>& house, const vector<Pos>& chicken_place)
{
	int ret = 0;
	
	for (auto i : house)
	{
		int sum = 1000;
		for (auto j : chicken_place)
		{
			int temp_sum = 0;
			temp_sum += abs(j.r - i.r) + abs(j.c - i.c);
			if (temp_sum < sum) sum = temp_sum;
		}

		ret += sum;
	}
	
	return ret;
}

void dfs(const int& s)
{
	if (included[s]) return;
	if (candidate.size() == M)
	{
		int CityDist = findCityDist(house, candidate);
		if (CityDist < result) result = CityDist;
		candidate.erase(candidate.end() - 1);
		return;
	}

	candidate.push_back(chicken_place[s]);
	included[s] = true;

	for (int i = 0; i < chicken_place.size(); i++)
	{
		if (!included[i]) dfs(i);
	}

	included[s] = false;
}

int main()
{
	ifstream txt_input("input.txt");
	txt_input >> N >> M;

	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			txt_input >> Grid[r][c];
			if (Grid[r][c] == 1) house.push_back({ r, c });
			else if (Grid[r][c] == 2) chicken_place.push_back({ r,c });
		}
	}

	dfs(0);
	cout << result;

	return 0;
}
