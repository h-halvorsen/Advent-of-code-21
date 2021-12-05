#include <iostream>
#include <string>
#include <fstream>

#define RESULT 'b'

using std::endl;
using std::stoi;
using std::getline;
using std::string;

std::ifstream input;

void resultA(const string& path);
void resultB(const string& path);
int getSum(std::ifstream& stream);

int main()
{
	const string path = "./Data_in.txt";
	if (RESULT == 'a') resultA(path);
	else if (RESULT == 'b') resultB(path);
}

void resultA(const string &path)
{
	input.open(path);
	if (!input.good()) return;

	int val, lastVal, counter = 0;

	string line;
	getline(input, line);

	lastVal = stoi(line.c_str());

	while (getline(input, line))
	{
		val = stoi(line.c_str());
		if (val > lastVal) counter++;
		lastVal = val;
	}
	std::cout << endl << counter << endl;
	input.close();

	return;
}

void resultB(const string& path)
{
	input.open(path);
	if (!input.good()) return;

	int valA = 0, valB = 0, valC = 0, counter = 0, sum, lastSum;

	string line;
	for (int i = 0; i < 3; i++)
	{
		getline(input, line);
		valA = valB;
		valB = valC;
		valC = stoi(line.c_str());
	}
	lastSum = valA + valB + valC;

	while (getline(input, line))
	{
		valA = valB;
		valB = valC;
		valC = stoi(line.c_str());
		sum = valA + valB + valC;

 		if (sum > lastSum) counter++;

		lastSum = sum;
	}

	std::cout << endl << counter << endl;
	input.close();

	return;
}
