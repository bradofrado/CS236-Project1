#pragma once

#include <map>
#include <string>
#include "Relation.h"
#include "DatalogProgram.h"
#include "Predicate.h"

class Database 
{
private:
    map<string, Relation*> relations;

    void evaluateSchemes(vector<Predicate*> schemes);
    void evaluateFacts(vector<Predicate*> facts);
    //Relation* findRelation(string schemeName);
public:
    Database(vector<Predicate*> schemes, vector<Predicate*> facts);
    ~Database();

    string toString();
};