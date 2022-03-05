#include "Query.h"
#include <vector>
#include <map>
#include <string>

vector<int> Query::getConstants()
{
    vector<int> pos;

    for (unsigned int i = 0; i < size(); i++)
    {
        Parameter param = at(i);

        if (!param.isId)
        {
            pos.push_back(i);
        }
    }

    return pos;
}

map<string, vector<int>> Query::getVariables()
{
    map<string, vector<int>> pos;
    for (unsigned int i = 0; i < size(); i++)
    {
        Parameter param = at(i);

        if (param.isId)
        {
            pos[param.value].push_back(i);
        }
    }

    return pos;
}