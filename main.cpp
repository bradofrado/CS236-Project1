#include <fstream>
#include <iostream>
#include <vector>
#include "Token.h"
#include "Scanner.h"
using namespace std;

string getInput(string fileName);

int main(int argc, char* argv[]) 
{
    string fileName = "test.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }
    
    string input = getInput(fileName);

    Scanner s(input);

    vector<Token> tokens;

    Token t;

    do
    {
        t = s.scanToken();

        tokens.push_back(t);
        cout << t.toString() << endl;
    } while (t.getType() != _EOF);

    cout << "Total Tokens = " << tokens.size() << endl;
}

string getInput(string fileName)
{
    string input = "";
    char curr;

    ifstream in(fileName);

    if (!in.is_open())
    {
        cout << "Bad file " << fileName << endl;
        exit(0);
    }

    while (in.get(curr))
    {
        input += curr;
    }

    return input;
}