#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using std::endl;
using std::stoi;
using std::getline;
using std::string;

int main()
{
    std::ifstream input("./input.txt");
    if (!input.good()) return 1;

    string line;

    int depth = 0, distance = 0, aim = 0;

    while (getline(input, line))
    {
        string command, var;
        int val;

        std::stringstream stream(line);
        stream >> command >> var;

        val = stoi(var.c_str());

        switch (command[0])
        {
        case 'f':
        {
            distance += val;
            depth += val * aim;
            break;
        }
        case 'u':
        {
            aim -= val;
            break;
        }
        case 'd':
        {
            aim += val;
            break;
        }
        }
    }
    
    std::cout << depth * distance;
    std::cin.get();
    input.close();
    return 0;
}
