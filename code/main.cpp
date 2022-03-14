#include <fstream>
#include <iostream>
#include <vector>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include "Database.h"
#include "Interpreter.h"

using namespace std;

string getInput(string fileName);
vector<Token> scanTokens(string input, bool doCout = false);
DatalogProgram parseTokens(vector<Token>);
DatalogProgram parseProgram(string fileName, bool p1Cout = false, bool p2Cout = false);

int main(int argc, char* argv[]) 
{
    string fileName = "test.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }

    // DatalogProgram datalogProgram = parseProgram(fileName);
    
    // Interpreter interpreter(datalogProgram);

    // interpreter.run();

    Scheme scheme1( { "A", "B" } );
    Scheme scheme2( { "B", "C" } );
    Scheme scheme3( { "X", "Y" } );
    Scheme scheme4( { "X", "Y", "Z" } );
    Tuple tuple1( {"'1'", "'2'"} );
    Tuple tuple2( {"'3'", "'4'"} );
    Tuple tuple3( {"'1'", "'4'"} );
    Tuple tuple4( {"'1'", "'2'", "'4'"} );

    cout << Relation::joinable(scheme1, scheme2, tuple1, tuple2) << endl;
    cout << Relation::joinable(scheme2, scheme3, tuple1, tuple2) << endl;
    cout << Relation::joinable(scheme3, scheme4, tuple1, tuple4) << endl;
    cout << Relation::joinable(scheme3, scheme4, tuple3, tuple4) << endl;
}

DatalogProgram parseProgram(string fileName, bool p1Cout, bool p2Cout)
{
    string input = getInput(fileName);

    vector<Token> tokens = scanTokens(input, p1Cout);
    DatalogProgram program = parseTokens(tokens);

    if (p2Cout) 
    {
        cout << "Success!" << endl;
        cout << program.toString() << endl;
    }

    return program;
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

DatalogProgram parseTokens(vector<Token> tokens) 
{
    Parser p = Parser(tokens);
    bool compiled = p.parse();

    if (!compiled) 
    {
        cout << "Failure!" << endl;
        cout << "  " << p.getErrorToken().toString() << endl;
        exit(0);
    }

    return p.getDatalogProgram();
}
