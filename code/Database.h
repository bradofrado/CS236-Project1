#pragma once

#include <map>
#include <string>
#include "Relation.h"
#include "DatalogProgram.h"
#include "Predicate.h"

class Database : public map<string, Relation>
{
private:
    //map<string, Relation*> relations;

public:
    Database(map<string, Relation> relations) : map(relations){}
    Database() {}
    ~Database(){}

    Relation& getRelation(string name);

    string toString();
};