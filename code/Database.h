#pragma once

#include <vector>
#include "Relation.h"
#include "DatalogProgram.h"
#include "Predicate.h"

class Database 
{
private:
    vector<Relation> relations;

    void evaluateSchemes(vector<Predicate*> schemes);
    void evaluateFacts(vector<Predicate*> facts);
    Relation* findRelation(string schemeName);
public:
    Database(DatalogProgram DatalogProgram);
    ~Database(){}

    string toString();
};