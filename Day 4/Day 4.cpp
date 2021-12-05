#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "../data_structures/data_structures.h"

using namespace std;
using custl::linkedlist;

class board
{
private:
	bool state[5][5];
	int cell[5][5];

public:

private:
	bool isDone()
	{
		for (int row = 0; row < 5; row++)
		{
			int total = 0;
			for (int col = 0; col < 5; col++)
			{
				total += cell[row][col];
			}
			if (total == 5) return true;
		}
		for (int col = 0; col < 5; col++)
		{
			int total = 0;
			for (int row = 0; row < 5; row++)
			{
				total += cell[row][col];
			}
			if (total == 5) return true;
		}
		return false;
	}
	bool inBoard(int input)
	{
		for (int row = 0; row < 5; row++)
		{
			for (int col = 0; col < 5; col++)
			{
				if (cell[row][col] == input)
				{
					state[row][col] = true;
					return true;
				}
			}
		}
		return false;
	}
	int sum()
	{
		int total = 0;
		for (int row = 0; row < 5; row++)
		{
			for (int col = 0; col < 5; col++)
			{
				if (!state[row][col])
					total += cell[row][col];
			}
		}
		return total;
	}

public:
	board(const int input[5][5])
	{
		for (int row = 0; row < 5; row++)
		{
			for (int col = 0; col < 5; col++)
			{
				cell[row][col] = input[row][col];
				state[row][col] = false;
			}
		}

	}
	int check(int input)
	{
		if (inBoard(input)) 
			if (isDone())
				return sum();
		return -1;
	}

};

void setup(void* boardArray, ifstream& input);
int partA(linkedlist<board*>& boards, string& nums);

int main()
{
	linkedlist<board*> boards;

	ifstream input("./input.txt");
	if (input.bad()) return 1;
	
	string numbers, line;
	getline(input, numbers);
	getline(input, line);

	setup(&boards, input);

	input.close();

	cout << partA(boards, numbers);
	

}

void setup(void* boardArray, ifstream& input)
{
	string line;
	stringstream stream;
	linkedlist<board*>* boards = reinterpret_cast<linkedlist<board*>*>(boardArray);
	
	int data[5][5];

	for (int i = 0; i <= 100; i++)
	{
		for (int j = 0; j < 5; j++) {

			getline(input, line);
			stream.clear();
			stream << line;
			stream >> data[j][0] >> data[j][1] >> data[j][2] >> data[j][3] >> data[j][4];

		}
		getline(input, line);
		board* n = new board(data);
		boards->append(n);
	}

	return;
}

int partA(linkedlist<board*>& boards, string& nums)
{
	string line, val;
	stringstream stream(nums);
	int num, ans;

	for (int j = 0; j < 100 && stream.eofbit; j++)
	{
		stream >> num;
		for (int i = 0; i < 100; i++)
		{
			printf("Num: %i | board: %i\n", j, i);
			ans = boards[i]->check(num);
			if (ans != -1)
			{
				return ans * num;
			}
		}
	}
	return 0;
}

