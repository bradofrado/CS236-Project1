#include "Interpreter.h"
#include "Predicate.h"
#include "Scheme.h"
#include "Relation.h"

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
    for (auto& value : datalogProgram.getFacts()) {
        string name = value->getName();
        Relation& relation = database.getRelation(name);
        Tuple tuple(value->getParamNames());
        relation.addTuple(tuple);
    }
}

void Interpreter::run() 
{
    evaluateSchemes();
    evaluateFacts();
    
    cout << database.toString() << endl;
}