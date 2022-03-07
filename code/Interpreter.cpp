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
        int numResults = result.size();

        //Project the result
        result = result.project(projections);

        //Rename the result
        result = result.rename(newNames);

        //Get the result string
        string resultString = numResults > 0 ? "Yes(" + to_string(numResults) + ")" : "No";

        //Display the results of the query
        cout << dbQuery->toString() << "? " << resultString << endl;
        cout << result.toString();
    }
}