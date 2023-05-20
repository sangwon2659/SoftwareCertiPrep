#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

int N, M;
int Grid[101][101];
bool visited[101][101];

int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int depth = 1;
int totNum = 100000;

struct Pos
{
	int r;
	int c;
};

/*
시간초과 뜬다 (최단 거리 탐색을 할 때는 BFS를 써서 처음으로 목표지점에 도달하는 경로에서 거리를 출력하는 게 맞다
void dfs(const Pos& s)
{
	if (visited[s.r][s.c]) return;
	if (s.r == N && s.c == M)
	{
		if (totNum > depth) totNum = depth;
	}

	depth++;
	visited[s.r][s.c] = true;

	for (int i = 0; i < 4; i++)
	{
		int target_r = s.r + dy[i];
		int target_c = s.c + dx[i];
		if (target_r < 1 || target_r > N || target_c < 1 || target_c > M) continue;
		if (visited[target_r][target_c] || Grid[target_r][target_c] == 0) continue;
		dfs({target_r, target_c});
		visited[target_r][target_c] = false;
	}

	depth--;
}
*/

int main()
{
	ifstream txt_input("input.txt");
	txt_input >> N >> M;

	for (int r = 1; r <= N; r++)
	{
		string input;
		txt_input >> input;
		for (int c = 1; c <= M; c++)
		{
			if (input[c - 1] == 49) Grid[r][c] = 1;
			else Grid[r][c] = 0;
		}
	}

	dfs({ 1, 1 });
	cout << totNum;

	return 0;
}
