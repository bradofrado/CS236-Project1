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

        //Select all the constant values
        vector<int> constants = query.getConstants();
        for (auto& index : constants)
        {
            result = result.select(index, query.at(index).value);
        }

        //Select all the variable values
        map<string, vector<int>> variables = query.getVariables();
        for (map<string, vector<int>>::iterator it = variables.begin(); it != variables.end(); it++)
        {
            result = result.select(it->second);
        }

        int numResults = result.size();

        //Project the result
        vector<int> projections;
        for (auto& variable : variables)
        {
            int position = query.getParameterNamePosition(variable.first);
            projections.push_back(position);
        }
        result = result.project(projections);

        //Rename the result
        map<int, string> newNames;
        for (auto& variable : projections)
        {
            newNames[variable] = query.at(variable).value;
        }
        result = result.rename(newNames);

        //Get the result string
        string resultString = numResults > 0 ? "Yes(" + to_string(numResults) + ")" : "No";

        //Display the results of the query
        cout << dbQuery->toString() << "? " << resultString << endl;
        cout << result.toString();
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