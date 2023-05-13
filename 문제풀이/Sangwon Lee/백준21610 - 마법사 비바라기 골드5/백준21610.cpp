#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Map_Coor
{
	int rain;
	bool isCloud;
	bool isJustMoved;
	bool isJustDeleted;
};

int dy[9] = {-10, 0, -1, -1, -1, 0, 1, 1, 1 };
int dx[9] = {-10, -1, -1, 0, 1, 1, 1, 0, -1 };

int dy_copy[5] = {-10, -1, -1, 1, 1};
int dx_copy[5] = {-10, -1, 1, 1, -1};

int N, M;
Map_Coor base_map[51][51];
int vec_order[101][3];

void moveCloud(const int& dir, const int& magnitude)
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			if (base_map[r][c].isCloud == true)
			{
				base_map[r][c].isCloud = false;
				int target_pos_y = (r + 100 * N + dy[dir] * magnitude) % N;
				int target_pos_x = (c + 100 * N + dx[dir] * magnitude) % N;
				if (target_pos_y == 0) target_pos_y = 5;
				if (target_pos_x == 0) target_pos_x = 5;
				base_map[target_pos_y][target_pos_x].isJustMoved = true;
				base_map[target_pos_y][target_pos_x].rain++;
			}

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			if (base_map[r][c].isJustMoved)
			{
				base_map[r][c].isCloud = true;
				base_map[r][c].isJustMoved = false;
			}
}

void deleteCloud()
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			if (base_map[r][c].isCloud == true)
			{
				base_map[r][c].isCloud = false;
				base_map[r][c].isJustDeleted = true;
			}
}

void copyCloud()
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			if (base_map[r][c].isJustDeleted == true)
				for (int copy_dir = 1; copy_dir <= 4; copy_dir++)
				{
					if (r + dy_copy[copy_dir] < 1 || r + dy_copy[copy_dir] > N || c + dx_copy[copy_dir] < 1 || c + dx_copy[copy_dir] > N) continue;
					if (base_map[r + dy_copy[copy_dir]][c + dx_copy[copy_dir]].rain > 0) base_map[r][c].rain++;
				}
}

void appearCloud()
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
		{
			if (base_map[r][c].isJustDeleted == true)
			{
				base_map[r][c].isJustDeleted = false;
				continue;
			}

			if (base_map[r][c].rain >= 2)
			{
				base_map[r][c].isCloud = true;
				base_map[r][c].rain -= 2;
			}
		}
}

int sumWater()
{
	int sum = 0;
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			sum += base_map[r][c].rain;

	return sum;
}

void printBaseMap()
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			cout << base_map[r][c].rain << " ";
			if (base_map[r][c].isCloud) cout << "Cloud ";
			else cout << "      ";
		}
		cout << endl;
	}

	cout << "========================";
	cout << endl;
	cout << endl;
}

int main()
{
	fstream txt_input("input.txt");

	txt_input >> N >> M;
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
		{
			txt_input >> base_map[r][c].rain;
			if ((r == N - 1 && c == 1) || (r == N - 1 && c == 2) || (r == N && c == 1) || (r == N && c == 2))
				base_map[r][c].isCloud = true;
		}

	for (int i = 1; i <= M; i++)
	{
		txt_input >> vec_order[i][1];
		txt_input >> vec_order[i][2];
	}

	for (int repetition = 1; repetition <= M; repetition++)
	{
		moveCloud(vec_order[repetition][1], vec_order[repetition][2]);
		deleteCloud();
		copyCloud();
		appearCloud();

		printBaseMap();
	}

	int result;
	result = sumWater();
	cout << result;
}
