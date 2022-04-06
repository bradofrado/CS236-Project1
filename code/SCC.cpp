#include "SCC.h"
#include <string>
#include <stack>
#include <sstream>
#include <vector>

SCC::SCC(vector<int> ids, vector<Rule> rules) : vector<Rule>(rules) 
{
    stringstream ss;
    int size = ids.size();
    for (int i = 0; i < size; i++)
    {
        int id = ids.at(i);

        ss << "R" << id;
        if (i < size - 1) 
        {
            ss << ",";
        }
    }

    name = ss.str();
}

string SCC::toString() const
{
    return "SCC: " + name;
}

string SCC::getName() const
{
    return name;
}

//If there are multiple rules or a single rule depends on itself,
//then it is rule dependent (must run fix point)
bool SCC::isRuleDependent()
{
    if (size() > 1) return true;

    Rule rule = at(0);
    vector<Predicate> bodies = rule.getBodyPredicates();
    for (Predicate pred : bodies)
    {
        if (pred.getName() == rule.getName())
        {
            return true;
        }
    }

    return false;
}
