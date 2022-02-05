#include <fstream>
#include <iostream>
#include <vector>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"

using namespace std;

string getInput(string fileName);
vector<Token> scanTokens(string input, bool doCout = false);

int main(int argc, char* argv[]) 
{
    string fileName = "test.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }
    
    string input = getInput(fileName);

    vector<Token> tokens = scanTokens(input);

    Parser p = Parser(tokens);
    p.datalogProgram();
}



vector<Token> scanTokens(string input, bool doCout)
{
    Scanner s(input);

    vector<Token> tokens;

    Token t;

    do
    {
        t = s.scanToken();

        tokens.push_back(t);

        if (doCout)
            cout << t.toString() << endl;
    } while (t.getType() != _EOF);

    if (doCout)
        cout << "Total Tokens = " << tokens.size() << endl;

    return tokens;
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