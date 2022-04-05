#pragma once

#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"
#include "Node.h"
#include "SCC.h"
#include <stack>
#include <vector>

using namespace std;

class Interpreter
{
private:
    DatalogProgram datalogProgram;
    Database database;

    void evaluateSchemes();
    void evaluateFacts();
    void evaluateRulesOld();
    void evaluateRules();
    void evaluateRulesWithSCC(vector<SCC> sccs);
    void evaluateQueries();

    bool evaluateRule(vector<Rule> rules);

    Relation evaluatePredicate(Predicate predicate, int& numResults);
    Relation evaluatePredicate(Predicate predicate);
public:
    Interpreter(DatalogProgram datalogProgram);

    void run();

    static Graph makeGraph(const vector<Rule>& rules, bool reverse = false);
    static stack<int> dfsForest(Graph graph);
    static vector<int> dfs(int index, Graph& graph);

    vector<SCC> findSCC(stack<int> postOrders, Graph& graph);
};