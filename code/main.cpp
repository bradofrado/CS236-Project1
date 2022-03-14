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

    Relation studentRelation("students", Scheme( {"ID", "Name", "Major"} ));

    vector<string> studentValues[] = {
        {"'42'", "'Ann'", "'CS'"},
        {"'64'", "'Ned'", "'EE'"},
    };

    for (auto& value : studentValues)
        studentRelation.addTuple(Tuple(value));

    Relation courseRelation("courses", Scheme( {"ID", "Course"} ));

    vector<string> courseValues[] = {
        {"'42'", "'CS 100'"},
        {"'32'", "'CS 232'"},
    };

    for (auto& value : courseValues)
        courseRelation.addTuple(Tuple(value));

    studentRelation.join(courseRelation);
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
