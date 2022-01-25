#if DEBUG
#include <fstream>
#endif

#include <iostream>
#include <vector>
#include "Token.h"
#include "Scanner.h"
using namespace std;

int main(int argc, char* argv[]) 
{
    string input = "";
    string curr;

#if DEBUG
ifstream in("test.txt");
    while (getline(in, curr))
    {
        input += curr;
        input += '\n';
    }

    input = input.substr(0, input.size() - 1);
#else
    while (getline(cin, curr))
    {
        input += curr;
        input += '\n';
    }

    input = input.substr(0, input.size() - 1);
#endif
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