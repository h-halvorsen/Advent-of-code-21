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
    input.close();
    printf("X-Max: %i, Y-Max: %i\n", output.x, output.y);
    return output;
}

void clean(const string inFile, const string& outFile)
{
    ifstream input(inFile);
    if (input.bad()) return;
    string line;
    
    while (getline(input, line))
    {

    }
    
    input.close();
    return;
}

int main()
{
    const string inFile = "./input.txt";
    const string temp1 = "./tmp1.txt";
    const string temp2 = "./tmp2.txt";
    const string outFile = "./output.txt";

    preProc(inFile, temp1);
    clean(temp1, temp2);
    cord extreme = max(temp1);
    


}

