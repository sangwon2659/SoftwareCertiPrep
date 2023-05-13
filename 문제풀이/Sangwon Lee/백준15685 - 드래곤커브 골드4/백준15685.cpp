#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Coordinate
{
	int y;
	int x;
};

const int MAPSIZE = 101;
vector<vector<bool>> map(MAPSIZE, vector<bool>(MAPSIZE));
vector<vector<int>> input;
int N;
vector<int> dy = {0, -1, 0, 1};
vector<int> dx = {1, 0, -1, 0};
vector<Coordinate> vCurve;

void collectInput()
{
	int x, y, d, g;
	ifstream txt_input("input.txt");
	txt_input >> N;
	for (int i = 0; i < N; i++)
	{
		txt_input >> x >> y >> d >> g;
		input.push_back({ x, y, d, g });
	}
}

// 나머지 curve 만들어주는 함수
void createSubCurve()
{
	Coordinate endpoint = vCurve[vCurve.size() - 1];
	int vCurvesize = vCurve.size();
	for (int vertex = vCurvesize - 2; vertex >= 0; vertex--)
	{
		int newY = (vCurve[vertex].x - endpoint.x) + endpoint.y;
		int newX = -(vCurve[vertex].y - endpoint.y) + endpoint.x;
		vCurve.push_back({ newY, newX });
	}
}

void createCurve()
{
	for (int curveloop = 0; curveloop < N; curveloop++)
	{
		int x, y, d, g;
		x = input[curveloop][0];
		y = input[curveloop][1];
		d = input[curveloop][2];
		g = input[curveloop][3];


		//cout << "Loop " << curveloop << "[" << x << ", " << y << ", " << d << ", " << g << "]" << endl;

		// 0세대 만들기
		vCurve.push_back({ y, x });
		vCurve.push_back({ y + dy[d], x + dx[d] });

		// g에 따라 나머지 curve 만들기
		for (int subcurveloop = 0; subcurveloop < g; subcurveloop++)
		{
			//cout << "Generation: " << subcurveloop + 1 << endl;
			createSubCurve();
			//for (auto i : vCurve) cout << "{" << i.x << "," << i.y << "} ";
			//cout << endl;
		}

		for (auto i : vCurve)
		{
			map[i.y][i.x] = true;
		}
		//cout << endl;

		vCurve.clear();
	}
}

// 꼭지점이 모두 curve의 일부인 1x1 사각형의 개수 찾는 함수
{
int countSquare()
	int sumsquare = 0;
	for (int r = 0; r < MAPSIZE - 2; r++)
		for (int c = 0; c < MAPSIZE - 2; c++)
			if (map[r][c] == true && map[r + 1][c] == true && map[r][c + 1] == true && map[r + 1][c + 1] == true)
				sumsquare++;
	return sumsquare;
}

int main()
{
	collectInput();
	createCurve();
	cout << countSquare();

	return 0;
}
