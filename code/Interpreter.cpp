#include "Interpreter.h"
#include "Predicate.h"
#include "Scheme.h"
#include "Relation.h"
#include "Query.h"
#include "Graph.h"
#include "SCC.h"
#include <map>
#include <string>

using namespace std;

Interpreter::Interpreter(DatalogProgram datalogProgram)
{
    this->datalogProgram = datalogProgram;
}

void Interpreter::run() 
{
    evaluateSchemes();
    evaluateFacts();
    evaluateRules();
    evaluateQueries();
}

void Interpreter::evaluateSchemes() 
{
    map<string, Relation> relations;
    //Make the schemes
    for (auto& dpScheme : datalogProgram.getSchemes())
    {
        string name = dpScheme.getName();

        Scheme scheme(dpScheme.getParamNames());
        Relation relation(name, scheme);

        relations.insert(pair<string, Relation>(name,relation));
    }

    database = Database(relations);
}

void Interpreter::evaluateFacts()
{
    for (auto& fact : datalogProgram.getFacts()) {
        string name = fact.getName();
        Relation& relation = database.getRelation(name);
        Tuple tuple(fact.getParamNames());
        relation.addTuple(tuple);
    }
}

void Interpreter::evaluateRules()
{
    // Build the dependency graph.
    Graph dependencyGraph = Interpreter::makeGraph(datalogProgram.getRules());

    cout << "Dependency Graph" << endl << dependencyGraph.toString() << endl;

    //Build the reverse dependency graph.
    Graph reverseGraph = Interpreter::makeGraph(datalogProgram.getRules(), true);

    //Run DFS-Forest on the reverse dependency graph.
    stack<int> postOrders = Interpreter::dfsForest(reverseGraph);

    //Find the strongly connected components (SCCs).
    vector<SCC> sccs = findSCC(postOrders, dependencyGraph);
    
    //Evaluate the rules in each component.
    evaluateRulesWithSCC(sccs);
}

void Interpreter::evaluateRulesWithSCC(vector<SCC> sccs)
{
    cout << "Rule Evaluation" << endl;

    for (SCC scc : sccs)
    {
        cout << scc.toString() << endl;
        int i = 0;
        do
        {
            //Only evaluate scc that aren't rule dependent once (have one rule not itself)
            if (!scc.isRuleDependent() && i > 0)
            {
                break;
            }

            i++;
        } while (evaluateRule(scc));

       cout << i << " passes: " << scc.getName() << endl;
    }

    cout << endl;
}

void Interpreter::evaluateRulesOld()
{
    cout << "Rule Evaluation" << endl;
    int i = 0;
    do
    {
       i++;
    } while (evaluateRule(datalogProgram.getRules()));

    cout << endl << "Schemes populated after " << i << " passes through the Rules." << endl << endl;
}

bool Interpreter::evaluateRule(vector<Rule> rules)
{
    bool changed = false;
    for (Rule& rule : rules)
    {
        cout << rule.toString() << endl;

        vector<Relation> immediateResults;
        //Get the immediate results
        for (Predicate& predicate : rule.getBodyPredicates())
        {
            Relation result = evaluatePredicate(predicate);
            immediateResults.push_back(result);
        }

        //Join them
        Relation result = immediateResults.at(0);
        result.setName(rule.getName());
        for (unsigned int i = 1; i < immediateResults.size(); i++)
        {
            result = result.join(immediateResults.at(i));
        }

        //Project the needed columns
        result = result.project(rule.getHeadPredicate().getParamNames());

        //Rename to the original column
        Relation& original = database.getRelation(result.getName());
        int sizeBefore = original.size();
        
        //To prevent an invalid argument error
        if (result.size() > 0) {
            result = result.rename(original.getSchemeNames());

            Relation diff = result.diff(original);

            original = original.Union(result);

            //If there was a change, make it known
            if (original.size() > sizeBefore)
            {
                changed = true;
                cout << diff.toString() << endl;
            }
        }
    }

    return changed;
}

Relation Interpreter::evaluatePredicate(Predicate predicate)
{
    int numResults;
    return evaluatePredicate(predicate, numResults);
}

Relation Interpreter::evaluatePredicate(Predicate predicate, int& numResults)
{
    Relation& relation = database.getRelation(predicate.getName());

    Query query(predicate.getParams());
    Relation result = relation;
    
    vector<int> projections;
    vector<string> newNames;
    
    //Select all the constant values
    vector<int> constants = query.getConstants();
    for (auto& index : constants)
    {
        result = result.select(index, query.at(index).value);
    }

    //Select all the variable values
    map<string, vector<int>> variables = query.getVariables();

    int currIt = 0;
    for (auto& variable : variables)
    {
        result = result.select(variable.second);

        //Optimized: get the projection indexes
        int position = query.getParameterNamePosition(variable.first);

        //The positions need to be sorted for this to work
        //If it needs to be sorted, find where to put it
        if (currIt > 0 && position < projections.at(currIt - 1)) 
        {
            int index = currIt;
            while (index > 0 && position < projections.at(index - 1))
            {
                index--;
            }
            projections.insert(projections.begin() + index, position);

            //Optimized: get the rename mapping
            newNames.insert(newNames.begin() + index, variable.first);
        }
        //Otherwise stick it on the end
        else
        {
            projections.push_back(position);

            //Optimized: get the rename mapping
            newNames.push_back(variable.first);
        }
        

        currIt++;
    }

    //Get the result size
    numResults = result.size();

    //Project the result
    result = result.project(projections);

    //Rename the result
    result = result.rename(newNames);

    return result;
}

void Interpreter::evaluateQueries()
{
    cout << "Query Evaluation" << endl;
    for (auto& dbQuery : datalogProgram.getQueries())
    {
        int numResults;
        Relation result = evaluatePredicate(dbQuery, numResults);

        //Get the result string
        string resultString = numResults > 0 ? "Yes(" + to_string(numResults) + ")" : "No";

        //Display the results of the query
        cout << dbQuery.toString() << "? " << resultString << endl;

        if (result.size() > 0) {
            cout << result.toString() << endl;
        }
    }
}

Graph Interpreter::makeGraph(const vector<Rule>& rules, bool reverse)
{
    Graph graph(rules.size());

    for (unsigned fromID = 0; fromID < rules.size(); fromID++) {
        const Rule& fromRule = rules.at(fromID);

        vector<Predicate> bodyPredicates = fromRule.getBodyPredicates();
        for (unsigned pred = 0; pred < bodyPredicates.size(); pred++) {
            const Predicate& bodyPred = bodyPredicates.at(pred);

            for (unsigned toID = 0; toID < rules.size(); toID++) {
                const Rule& toRule = rules.at(toID); 

                Predicate headPred = toRule.getHeadPredicate();
                if (headPred.getName() == bodyPred.getName()) {     
                    if (reverse) {
                        graph.addEdge(toID, fromID);
                    }  
                    else {
                        graph.addEdge(fromID, toID);
                    }
                }
            }
        }
    }

    return graph;
}

//2
//1
//0

//4
//3
//5

//5
//3
//4
stack<int> mergeStacks(stack<int> s1, stack<int> s2)
{
    int size = s2.size();
    stack<int> empty;
    for (int i = 0; i < size; i++)
    {
        int top = s2.top();
        s2.pop();
        empty.push(top);
    }

    for (int i = 0; i < size; i++)
    {
        int top = empty.top();
        empty.pop();
        s1.push(top);
    }

    return s1;
}

vector<int> mergeLists(vector<int> s1, vector<int> s2)
{
    for (int id : s2)
    {
        s1.push_back(id);
    }

    return s1;
}

stack<int> Interpreter::dfsForest(Graph graph)
{
    stack<int> nodes;

    for (auto& pair : graph)
    {
        if (!pair.second.marked())
        {
            stack<int> curr = dfs(pair.first, graph);

            nodes = mergeStacks(nodes, curr);
            //nodes.push(pair.first);
        }
    }

    return nodes;
}

stack<int> Interpreter::dfs(int index, Graph& graph)
{
    Node& node = graph.at(index);

    if (node.marked())
    {
        return stack<int>();
    }

    node.mark();

    stack<int> nodes;
    for (auto& Id : node)
    {
        Node& curr = graph.at(Id);

        if (!curr.marked())
        {
            stack<int> list = dfs(Id, graph);
            nodes = mergeStacks(nodes, list);
            //nodes.push_back(Id);
        }
    }

    nodes.push(index);

    return nodes;
}

vector<SCC> Interpreter::findSCC(stack<int> postOrders, Graph& graph)
{
    vector<SCC> sccs;
    graph.unmarkNodes();

    int size = postOrders.size();
    for (int i = 0; i < size; i++)
    {
        int top = postOrders.top();
        postOrders.pop();

        stack<int> orders = dfs(top, graph);

        vector<Rule> rules;
        SCC scc(orders, rules);
        int size = orders.size();
        for (int i = 0; i < size; i++)
        {
            int top = orders.top();
            orders.pop();

            scc.push_back(datalogProgram.getRules().at(top));
        }

        if (scc.size() > 0)
        {
            sccs.push_back(scc);
        }
        
    }

    return sccs;
}