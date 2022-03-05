#include "Database.h"
#include "Relation.h"
#include "Scheme.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include <string>
#include <sstream>
#include <iterator>
#include <map>

using namespace std;

Database::Database(vector<Predicate*> schemes, vector<Predicate*> facts) 
{
    evaluateSchemes(schemes);
    evaluateFacts(facts);
}

Database::~Database() 
{
    for (map<string,Relation*>::iterator it = relations.begin(); it != relations.end(); it++) 
    {
        Relation* relation = it->second;

        delete relation;
    }
}

void Database::evaluateSchemes(vector<Predicate*> schemes) 
{
    //Make the schemes
    for (auto& dpScheme : schemes)
    {
        string name = dpScheme->getName();

        Scheme scheme(dpScheme->getParamNames());
        Relation* relation = new Relation(name, scheme);

        relations.insert(pair<string, Relation*>(name,relation));
    }
}

void Database::evaluateFacts(vector<Predicate*> facts)
{
    for (auto& value : facts) {
        string name = value->getName();
        Relation* relation = relations[name];
        Tuple tuple(value->getParamNames());
        relation->addTuple(tuple);
    }
}

// Relation* Database::findRelation(string schemeName) 
// {
//     for (auto& relation : relations) 
//     {
//         if (relation.getName() == schemeName)
//         {
//             return &relation;
//         }
//     }

//     throw "Cannot find the relation with the name " + schemeName;
// }

string Database::toString()
{
    stringstream ss;

    for (map<string,Relation*>::iterator it = relations.begin(); it != relations.end(); it++) 
    {
        ss << it->second->toString() << endl;
    }

    return ss.str();
}