#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


const int LINE_COUNT = 1000;

using std::endl;
using std::stoi;
using std::getline;
using std::string;

std::ifstream input;

int most_common(const std::vector<int>& list, bool inverted = false);
int partB(std::vector<int> list, bool inverted);

int main()
{
	input.open("./input.txt");
	if (input.bad()) return 1;

	string line;

	std::vector<int> inList;
	
	inList.reserve(1000);
	
	while (getline(input, line))
	{
		inList.push_back(stoi(line, 0, 2));
	}


	/*--------Part A--------*/
	int ans1 = most_common(inList);
	printf(
		"Part A: Gamma:%i, Epsilon:%i, Power:%i\n", 
		ans1, 
		ans1 ^ 0xfff, 
		ans1 * (ans1 ^ 0xfff));

	/*--------Part B--------*/
	bool run = true;
	int o2 = partB(inList, false);
	int co2 = partB(inList, true);

	printf(
		"Part B: Oxygen:%i, CO2:%i, Life support:%i\n",
		o2,
		co2,
		o2 * co2);

}

int most_common(const std::vector<int>& list, bool inverted)
{
	uint32_t gamma = 0;
	int count[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (int i = 0; i < list.size(); i++)
	{
		for (int j = 0; j < 12; j++)
		{
			count[j] += (list[i] >> (11 - j)) & 1;
		}
	}

	for (int i = 0; i < 12; i++)
	{
		if (inverted && (count[i] >= (list.size() / 2)))
		{
			gamma += 1 << (11 - i);
		}
		else if (!inverted && (count[i] > (list.size() / 2)))
		{
			gamma += 1 << (11 - i);
		}
	}
	gamma = inverted ? (gamma ^ 0xfff) : gamma;
	return gamma;
		
}

int partB(std::vector<int> list, bool inverted)
{
	int common = most_common(list, inverted);
	for (int i = 0; i < 12 ; i++)
	{
		for (int j = 0; j < list.size(); j++)
		{
			if ((list[j] & (1 << (11-i))) != (common & (1 << (11 - i))))
			{
				list.erase(list.begin() + j--);
			}
		}
		if (list.size() == 1) return list[0];
		if (list.size() > 2) common = most_common(list, inverted);
	}
	return 0;
}