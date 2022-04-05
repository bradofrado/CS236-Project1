#include "SCC.h"
#include <string>
#include <stack>
#include <sstream>
#include <vector>

SCC::SCC(stack<int> ids, vector<Rule> rules) : vector<Rule>(rules) 
{
    stringstream ss;
    int size = ids.size();
    for (int i = 0; i < size; i++)
    {
        int top = ids.top();
        ids.pop();

        ss << "R" << top;
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

bool SCC::isRuleDependent()
{
    return size() > 1 || at(0).getBodyPredicates().size() > 1 || at(0).getName() == at(0).getBodyPredicates().at(0).getName();
}