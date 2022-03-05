#include "Database.h"
#include "Relation.h"
#include "Scheme.h"
#include "DatalogProgram.h"
#include <string>
#include <sstream>

Database::Database(DatalogProgram DatalogProgram) 
{
    //Make the schemes
    // for (auto& dpScheme : DatalogProgram.getSchemes())
    // {
    //     string name = dpScheme->getName();

    //     Scheme scheme(dpScheme->getParamNames());
    //     Relation relation(name, scheme);

    //     for (auto& value : DatalogProgram.getFacts()) {
    //         if (value->getName() == name) {
    //             Tuple tuple(value->getParamNames());
    //             relation.addTuple(tuple);
    //         }
    //     }

    //     relations.push_back(relation);
    // }

    evaluateSchemes(DatalogProgram.getSchemes());
    evaluateFacts(DatalogProgram.getFacts());
}

void Database::evaluateSchemes(vector<Predicate*> schemes) 
{
    //Make the schemes
    for (auto& dpScheme : schemes)
    {
        string name = dpScheme->getName();

        Scheme scheme(dpScheme->getParamNames());
        Relation relation(name, scheme);

        relations.push_back(relation);
    }
}

void Database::evaluateFacts(vector<Predicate*> facts)
{
    for (auto& value : facts) {
        Relation* relation = findRelation(value->getName());
        Tuple tuple(value->getParamNames());
        relation->addTuple(tuple);
    }
}

Relation* Database::findRelation(string schemeName) 
{
    for (auto& relation : relations) 
    {
        if (relation.getName() == schemeName)
        {
            return &relation;
        }
    }

    throw "Cannot find the relation with the name " + schemeName;
}

string Database::toString()
{
    stringstream ss;

    for (auto& relation : relations) 
    {
        ss << relation.toString() << endl;
    }

    return ss.str();
}