#include <vector>
#include <string>
#include "Predicate.h"
#include "Rule.h"
#include <sstream>

using namespace std;

string Rule::toString()
{
    stringstream ss;

    ss << headPredicate.toString() << " :- ";

    for (unsigned int i = 0; i < bodyPredicates.size(); i++)
    {
        ss << bodyPredicates.at(i).toString();

        if (i < bodyPredicates.size() -1 )
        {
            ss << ",";
        }
    }

    return ss.str();
}

void Rule::addPredicate(Predicate predicate)
{
    bodyPredicates.push_back(predicate);
}