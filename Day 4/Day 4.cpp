#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class board
{
private:
	uint8_t* state = new uint8_t[5];
	int* cell = new int[5 * 5];
public:
private:
public:
	board()
	{
		for (int row = 0; row < 5; row++)
		{
			state[row] = 0;
			
			for (int col = 0; col < 5; col++)
			{
				cell[row * 5 + col] = 0;
			}
		}

	}
	bool isDone()
	{
		for (int row = 0; row < 5; row++)
		{
			if (state[row] == 0xff)
			{
				return true;
			}
			int collumnSum = 0;
			for (int col = 0; col < 5; col++)
			{
				collumnSum = (state[row] << col) & 16;
			}
		}
	}
};

int main()
{
	ifstream input("./input.txt");
	vector<board> boards;
	boards.reserve(100);
}