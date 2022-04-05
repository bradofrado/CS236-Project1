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
#include "Node.h"
#include "Graph.h"

using namespace std;

string getInput(string fileName);
vector<Token> scanTokens(string input, bool doCout = false);
DatalogProgram parseTokens(vector<Token>);
DatalogProgram parseProgram(string fileName, bool p1Cout = false, bool p2Cout = false);
void test();

int main(int argc, char* argv[]) 
{
    string fileName = "test.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }

    DatalogProgram datalogProgram = parseProgram(fileName);
    
    Interpreter interpreter(datalogProgram);

    interpreter.run();

    //test();
}


void test()
{   
    // Node node;
    // node.addEdge(4);
    // node.addEdge(8);
    // node.addEdge(2);
    // cout << node.toString() << endl;
    
    // Graph graph(3);
    // graph.addEdge(1,2);
    // graph.addEdge(1,0);
    // graph.addEdge(0,1);
    // graph.addEdge(1,1);
    // cout << graph.toString();

    // predicate names for fake rules
    // first is name for head predicate
    // second is names for body predicates
    
    // pair<string,vector<string>> ruleNames[] = {
    //     { "A", { "B" } },
    //     { "B", { "B", "A" } },
    // };

    // pair<string,vector<string>> ruleNames[] = {
    //     { "Sibling", { "Sibling" } },
    //     { "Ancestor", { "Ancestor", "Parent" } },
    //     { "Ancestor", { "Parent" } },
    // };

    pair<string,vector<string>> ruleNames[] = {
        { "A", { "B", "C" } },
        { "B", { "A", "D" } },
        { "B", { "B" } },
        { "E", { "F", "G" } },
        { "E", { "E", "F" } },
    };

    vector<Rule> rules;

    for (auto& rulePair : ruleNames) {
        string headName = rulePair.first;
        Predicate headPredicate(headName);
        Rule rule = Rule(headPredicate);
        vector<string> bodyNames = rulePair.second;
        for (auto& bodyName : bodyNames) {
            Predicate bodyPredicate(bodyName);
            rule.addPredicate(bodyPredicate);
        }
        rules.push_back(rule);
    }

    Graph graph = Interpreter::makeGraph(rules);
    Graph reverseGraph = Interpreter::makeGraph(rules, true);
    stack<int> postOrders = Interpreter::dfsForest(reverseGraph);

    int size = postOrders.size();
    for (int i = 0; i < size; i++)
    {
        cout << postOrders.top() << endl;
        postOrders.pop();
    }
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
