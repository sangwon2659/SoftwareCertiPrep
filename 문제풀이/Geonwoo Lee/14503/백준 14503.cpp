#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

int rotate(int &d)
{
	if (d == 0)				 // 반시계 방향 회전
		d = 3;
	else
		d -= 1;
	return d;
}



int main()
{

	ifstream txt_input("input.txt");

	int n, m, r, c, d; // 맵 (N,M), 로봇의 현재 위치 (r,c), 로봇의 방향 (d)
	txt_input >> n >> m >> r >> c >> d;
	
	vector<vector<int>> base_map(n, vector<int>(m));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			txt_input >> base_map[i][j];
		}
	}

	int cnt = 0; // 청소 횟수
	

	while (1)
	{
		if(base_map[r][c]==0)
			base_map[r][c] = -1; // cleaned
			
		int& north = base_map[r-1][c ];
		int& west = base_map[r ][c-1];
		int& east = base_map[r ][c+1];
		int& south = base_map[r+1][c];
		//vector<int> order{ north,east,south,west };

		if (north != 0 && west != 0 && south != 0 && east != 0) //현재 칸의 주변 4칸중 0이 없는 경우
		{
			
			if (d == 0 && south != 1) //후진 가능하면
			{
				r += 1;

			}
			else if (d == 1 && west != 1)
			{
				c -= 1;

			}
			else if (d == 2 && north != 1)
			{

				r -= 1;
			}
			else if (d == 3 && east != 1)
			{
				c += 1;

			}
			else // 후진 불가능
				break;
		}
		else if(north == 0 || west == 0 || south == 0 || east == 0)	//현재 칸의 주변 4칸중 0이 있는 경우
		{
			while(1)
			{
				rotate(d);
				//cout << d << endl;
				if (d == 0 && north == 0) {			//앞쪽 칸 0 이면 전진
					r -= 1;
					break;
				}
				else if (d == 1 && east == 0) {
					c += 1;
					break;
				}
				else if (d == 2 && south == 0) {
					r += 1;
					break;
				}
				else if (d == 3 && west == 0) {
					c -= 1;
					break;
				}
				else
					break;
			}
			

		}
			
			
			
			

		/* base_map 출력
		for (int i = 0; i < n; i++) 
		{
			for (int j = 0; j < m; j++)
			{
				cout.width(3);
				cout << base_map[i][j];
				
			}
			cout << endl;
		}
		cout << endl;*/
	}
	for (int i = 0; i < n; i++) //-1 세기
	{
		for (int j = 0; j < m; j++)
		{
			if (base_map[i][j] == -1)
				cnt++;
		}
	}
	std::cout << cnt;
}
