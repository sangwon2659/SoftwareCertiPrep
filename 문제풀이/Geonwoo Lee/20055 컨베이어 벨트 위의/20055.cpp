#include <iostream>
#include <vector>
#include <fstream>
#include <queue> 

using namespace std;

//선언
int n, k, cnt=0;
int round_cnt = 0;
int move_done = 0;
int belt_start = 0;
int belt_end = n;
queue<int> robot;

struct belt {
	int endurance;
	bool isVisited;

} belt[202] = { 0,false };

void get_Info()
{
	ifstream txt_input("input.txt");

	txt_input >> n >> k;

	for (int i = 0; i < 2 * n; i++)
	{
		txt_input >> belt[i].endurance;
	}
}

void move_Belt()
{
	if (belt_start == 0)
		belt_start = 2 * n - 1;
	else
		belt_start--;
	if (belt_end == 0)
		belt_end = 2 * n - 1;
	else
		belt_end--; 
	//round_cnt++;
}

void move_Robot()
{
	for (int i = 0; i < robot.size(); i++)
	{
		belt[robot.front()].isVisited = false;	// 현재 벨트에서 로봇 비우기
		//if (belt[i].endurance == 0) cnt++;
		if (robot.front() == belt_end)	//로봇이 끝단일 때
		{
			continue;
		}
		if (robot.front() == 2 * n - 1)	//0일 때
		{
			if (belt[0].endurance > 0 && belt[0].isVisited == false) //앞으로이동
			{
				belt[0].isVisited = true;
				belt[0].endurance--;
				robot.push(0);
				//if (belt[0].endurance == 0) cnt++;
			}
		}
		if (belt[robot.front() + 1].endurance > 0 && belt[robot.front() + 1].isVisited == false) //앞으로이동
		{
			belt[robot.front() + 1].isVisited = true;
			belt[robot.front() + 1].endurance--;
			robot.push(robot.front()+1); 
			//if (belt[robot.front() + 1].endurance == 0) cnt++;
		}
		else  //만약 이동할 수 없다면 가만히 있는다
		{
			belt[robot.front()].isVisited = true;
			robot.push(robot.front());
		}
		
		robot.pop();
		
	}
	round_cnt++;
}

void make_Robot()
{
	if (belt[belt_start].endurance > 0 && belt[belt_start].isVisited == false)
	{
		robot.push(belt_start);
		belt[belt_start].isVisited = true;
		belt[belt_start].endurance--;
		
	}
	round_cnt++;
	//if (belt[belt_start].endurance == 0) cnt++;
}

void check()
{
	for (int i = 0; i < 2 * n; i++)
	{
		if (belt[i].endurance == 0)
		{
			cnt++;
			if (cnt == k) break;
		}
	}
	
}

int main()
{
	get_Info();
	
	while (cnt != k)
	{
		move_Belt(); 
		
		move_Robot();
		
		make_Robot();
		//if (cnt == k)
			
		check();
		round_cnt++;
	}
	cout << round_cnt;
}



































/*
struct conveyor {
	int endurance;
	bool robot;

	conveyor(int e, bool r) :endurance(e), robot(r) {}
};
deque<conveyor> convey;	

int main()
{
	ifstream txt_input("input.txt");
	int n, k, endurance;

	txt_input >> n >> k;

	int round = 0; //단계


	for (int i = 0; i < 2 * n; i++)
	{
		txt_input >> endurance;
		convey.push_back(conveyor(endurance, false));
	}

	for (int i = 0; i < convey.size(); i++)
	{
		conveyor el = convey[i];
		cout << el.endurance;
	}

	while (convey.size()!=2*n-k)
	{

	}
}



	
	int start = 0;
	int endn = 2*n;

	int loadn = 0;
	int unloadn = n;

	while (true)
	{
		if (convey[start].endurance == 0)
		{
			continue;
		}
		else
		{
			convey[start].robot = true; //로봇올리기
			convey[start].endurance--;
			
			if (start == 0)
				start = 2 * n;
			if (endn == 0)
				endn = 2 * n;
			else
			{
				start--;
				endn--;
			}
			convey[start].endurance--;	//이동하면서 내구성 -1
			
			loadn = start;
			if (unloadn == 0)
				unloadn = n;
			else
				unloadn--;

			if(start==n)
			{

		}
		
	}

	


	for (int i = 0; i < n; i++)		//로봇 움직임
	{
		if (convey[i].endurance == 0)
		{
			cnt++;
			if (cnt == k)
				break;
		}
		else
		{
			convey[i].robot = true;
			convey[i].endurance--;
			if (convey[i + 1].endurance != 0 && convey[i + 1].robot == false)
			{
				convey[i + 1].robot = true;
				convey[i].robot = false;
				convey[i + 1].endurance--;
			}
		}
		
		
		

		round++;
	}
	

	cout <<convey[1].endurance<< round;
}*/
