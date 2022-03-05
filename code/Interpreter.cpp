#include "Interpreter.h"
#include "Predicate.h"
#include "Scheme.h"
#include "Relation.h"
#include "Query.h"
#include <map>
#include <string>

using namespace std;

Interpreter::Interpreter(DatalogProgram datalogProgram)
{
    this->datalogProgram = datalogProgram;
}

void Interpreter::evaluateSchemes() 
{
    map<string, Relation> relations;
    //Make the schemes
    for (auto& dpScheme : datalogProgram.getSchemes())
    {
        string name = dpScheme->getName();

        Scheme scheme(dpScheme->getParamNames());
        Relation relation(name, scheme);

        relations.insert(pair<string, Relation>(name,relation));
    }

    database = Database(relations);
}

void Interpreter::evaluateFacts()
{
    for (auto& fact : datalogProgram.getFacts()) {
        string name = fact->getName();
        Relation& relation = database.getRelation(name);
        Tuple tuple(fact->getParamNames());
        relation.addTuple(tuple);
    }
}

void Interpreter::evaluateRules()
{

}

void Interpreter::evaluateQueries()
{
    for (auto& dbQuery : datalogProgram.getQueries())
    {
        Relation& relation = database.getRelation(dbQuery->getName());

        Query query(dbQuery->getParams());
        Relation result = relation;
        vector<int> constants = query.getConstants();
        map<string, vector<int>> variables = query.getVariables();

        for (auto& index : constants)
        {
            result = result.select(index, query.at(index).value);
        }

        for (map<string, vector<int>>::iterator it = variables.begin(); it != variables.end(); it++)
        {
            result = result.select(it->second);
        }

        cout << dbQuery->toString() << endl;
        cout << result.toString() << endl;
    }
}

void Interpreter::run() 
{
    evaluateSchemes();
    evaluateFacts();
    evaluateRules();
    evaluateQueries();

    //cout << database.toString() << endl;
}