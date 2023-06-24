#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <queue>

using namespace std;

struct Pos
{
	int x;
	int y;
};

int T, N;
Pos Home, Festival;
Pos ConvinienceStore[100];

int findDist(Pos CurrentPos, Pos Destination)
{
	int result = 0;
	result += abs(Destination.x - CurrentPos.x);
	result += abs(Destination.y - CurrentPos.y);

	return result;
}

void bfs()
{
	queue<Pos> q;
	q.push({ Home.x, Home.y });
	vector<bool> visited(N, false);

	while (!q.empty())
	{
		Pos v = q.front();
		q.pop();

		if (findDist(v, Festival) <= 1000)
		{
			cout << "happy" << endl;
			return;
		}

		for (int i = 0; i < N; i++)
		{
			if (visited[i]) continue;
			if (findDist(v, ConvinienceStore[i]) > 1000) continue;
			visited[i] = true;
			q.push(ConvinienceStore[i]);
		}
	}

	cout << "sad" << endl;
	return;
}

int main()
{
	ifstream txt_input("input.txt");
	txt_input >> T;

	for (int testcase = 0; testcase < T; testcase++)
	{
		txt_input >> N;

		int a, b;
		txt_input >> a >> b;
		Home.x = a;
		Home.y = b;

		for (int i = 0; i < N; i++)
		{
			int a, b;
			txt_input >> a >> b;
			ConvinienceStore[i].x = a;
			ConvinienceStore[i].y = b;
		}

		txt_input >> a >> b;
		Festival.x = a;
		Festival.y = b;

		bfs();
	}

	return 0;
}
