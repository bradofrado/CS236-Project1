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

string Database::toString()
{
    stringstream ss;

    for (map<string,Relation>::iterator it = begin(); it != end(); it++) 
    {
        ss << it->second.toString() << endl;
    }

    return ss.str();
}

Relation& Database::getRelation(string name)
{
    return at(name);
}