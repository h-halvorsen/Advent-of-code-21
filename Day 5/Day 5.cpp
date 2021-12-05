#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct cord
{
    int x;
    int y;
};

bool preProc(const string inFile, const string&outFile)
{
    ifstream input(inFile);
    if (input.bad()) return true;
    ofstream output(outFile);
    if (output.bad()) return true;

    string line;
    
    while (getline(input, line))
    {
        string sub1, sub2;
        int idx = line.find(',');
        line.replace(idx, 1, 1, ' ');
        idx = line.find(" -> ");
        line.replace(idx, 4, "\n");
        idx = line.find(',');
        line.replace(idx, 1, 1, ' ');
        line += "\n";
        output << line;
    }
    input.close();
    output.close();

    return false;
}

cord max(const string inFile)
{
    ifstream input(inFile);
    if (input.bad()) return { 0, 0 };
   
    string line;
    cord output{0,0};
    while (getline(input, line))
    {
        int x, y;
        stringstream stream(line);
        stream >> x >> y;

        if (x > output.x) output.x = x;
        if (y > output.y) output.y = y;

    }
    
    output.x++;
    output.y++;
    
    input.close();
    printf("X-Max: %i, Y-Max: %i\n", output.x, output.y);
    return output;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int partA(const string inFile, int* map, cord& size)
{
    ifstream input(inFile);
    if (input.bad()) return-1;

    string lineA, lineB;
    cord cordA, cordB;

    while (getline(input, lineA) && getline(input, lineB))
    {
        stringstream streamA(lineA);
        stringstream streamB(lineB);

        streamA >> cordA.x >> cordA.y;
        streamB >> cordB.x >> cordB.y;

        if (cordA.x == cordB.x)
        {
            int end = max(cordB.y, cordA.y);
            for (int i = min(cordB.y, cordA.y); i <= end; i++)
            {
                map[cordA.x + i * size.y]++;
            }
        }

        else if (cordA.y == cordB.y)
        {
            int end = max(cordB.x, cordA.x);
            for (int i = min(cordB.x, cordA.x); i <= end; i++)
            {
                map[i + cordA.y * size.y]++;
            }
        }
    }
    input.close();

    int count = 0;
    for (int i = 0; i < size.x * size.y; i++)
    {
        if (map[i] > 1) count ++;
    }
    return count;
}

int partB(const string inFile, int* map, cord& size)
{
    ifstream input(inFile);
    if (input.bad()) return-1;

    string lineA, lineB;
    cord a, b;

    while (getline(input, lineA) && getline(input, lineB))
    {
        stringstream streamA(lineA);
        stringstream streamB(lineB);

        streamA >> a.x >> a.y;
        streamB >> b.x >> b.y;

        if (abs(a.x - b.x) == abs(a.y - b.y))
        {
            int endCond = max(a.y, b.y);
            int start = min(a.x, b.x);
            for (int i = min(a.y, b.y); i <= endCond; i++)
            {
                map[start++ + i * size.y]++;
            }
        }
    }
    input.close();

    int count = 0;
    for (int i = 0; i < size.x * size.y; i++)
    {
        if (map[i] > 1) count++;
    }
    return count;
}

int main()
{
    const string inFile = "./input.txt";
    const string temp1 = "./tmp1.txt";
    const string temp2 = "./tmp2.txt";

    preProc(inFile, temp1);
    cord size = max(temp1);
    
    int* map = new int[size.x * size.y];
    for (int i = 0; i < size.x * size.y; i++)
    {
        map[i] = 0;
    }


    cout << "Part a: " << partA(temp2, map, size) << endl;
    cout << "Part b: " << partB(temp2, map, size) << endl;
}

