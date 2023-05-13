#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, M;
int pos_x, pos_y, dir;
int sum_cleaned_area = 0;

bool changeDirectionRobot(int&, const vector<vector<int>>&);
bool backMoveRobot(const int&, const vector<vector<int>>&);
bool forwardMoveRobot(const int&, vector<vector<int>>&);

int main()
{
	// For debugging purposes
	/*
	// Read text file
	ifstream txt_input("input.txt");

	// Acquire the size of the base map
	txt_input >> N >> M;
	// Acquire the x and y positions and direction of the robot
	txt_input >> pos_y >> pos_x >> dir;

	// Insert base map info from the text file
	vector<vector<int>> base_map(N, vector<int>(M));
	for (int r = 0; r < N; r++)
		for (int c = 0; c < M; c++)
			txt_input >> base_map[r][c];
	*/

	// Get data directly from platform
	// Get size of the base map and the initial status of the robot
	cin >> N >> M;
	cin >> pos_y >> pos_x >> dir;

	// Store data in a 2D vector
	vector<vector<int>> base_map(N, vector<int>(M));
	for (int r = 0; r < N; r++)
		for (int c = 0; c < M; c++)
			cin >> base_map[r][c];

	// Declare booleans to be used in the loop
	bool condition = true;
	bool exist_empty = false;
	bool forward_empty = false;
	bool back_empty = false;;

	while (condition)
	{
		// If the current position of the robot has not been visited, set it as 0 and increment the sum_cleaned_area variable
		if (base_map[pos_y][pos_x] == 0)
		{
			base_map[pos_y][pos_x] = 5;
			sum_cleaned_area++;
		}

		// Execute changeDirectionRobot function and have the result returned to exist_empty
		exist_empty = changeDirectionRobot(dir, base_map);

		// Execute forwardMoveRobot function and have the result returned to forward_empty
		forward_empty = forwardMoveRobot(dir, base_map);
	
		// Back move the robot if no area is empty
		if (!exist_empty)
		{
			back_empty = backMoveRobot(dir, base_map);
			// Break from while loop if back move is not possible
			if (!back_empty) condition = false;
		}
	}

	// Print the final sum_clean_area variable
	cout << sum_cleaned_area;

	return 0;
}

// Change direction in CCW direction if at least one out of four candidates is has yet been cleaned
bool changeDirectionRobot(int& input_dir, const vector<vector<int>>& base_map)
{
	if (base_map[pos_y - 1][pos_x] == 0 || base_map[pos_y][pos_x + 1] == 0 || base_map[pos_y + 1][pos_x] == 0 || base_map[pos_y][pos_x - 1] == 0)
	{
		switch (input_dir)
		{
		case 0: // North
			dir = 3; // To West
			break;

		case 1: // East
			dir = 0; // To North
			break;

		case 2: // South
			dir = 1; // To East
			break;

		case 3: // West
			dir = 2; // To South
			break;
		}

		return true;
	}
	return false;
}

// Check if forward area has not been cleaned and move forward if so
bool forwardMoveRobot(const int& input_dir, vector<vector<int>>& base_map)
{
	switch (input_dir)
	{
	case 0: // North
		if (base_map[pos_y - 1][pos_x] == 0)
		{
			base_map[pos_y - 1][pos_x] == 5;
			pos_y--;
			return true;
		}
		break;

	case 1: // East
		if (base_map[pos_y][pos_x + 1] == 0)
		{
			base_map[pos_y][pos_x + 1] == 5;
			pos_x++;
			return true;
		}
		break;

	case 2: // South
		if (base_map[pos_y + 1][pos_x] == 0)
		{
			pos_y++;
			base_map[pos_y + 1][pos_x] == 5;
			return true;
		}
		break;

	case 3: // West
		if (base_map[pos_y][pos_x - 1] == 0)
		{
			pos_x--;
			base_map[pos_y][pos_x - 1] == 5;
			return true;
		}
		break;
	}
	
	return false;
}

// Move robot backward if no wall behind
bool backMoveRobot(const int& dir, const vector<vector<int>>& base_map)
{
	bool ret = false;

	switch (dir)
	{
	case 0: //North
		if (base_map[pos_y + 1][pos_x] != 1)
		{
			pos_y++;
			ret = true;
		}
		break;

	case 1: // East
		if (base_map[pos_y][pos_x - 1] != 1)
		{
			pos_x--;
			ret = true;
		}
		break;

	case 2: // South
		if (base_map[pos_y - 1][pos_x] != 1)
		{
			pos_y--;
			ret = true;
		}
		break;

	case 3: // West
		if (base_map[pos_y][pos_x + 1] != 1)
		{
			pos_x++;
			ret = true;
		}
		break;
	}

	return ret;
}
