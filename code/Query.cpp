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

//Returns a map of the scheme position and all of the scheme positions that share this variable
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

int Query::getParameterNamePosition(string name)
{
    for (unsigned int i = 0; i < size(); i++)
    {
        Parameter param = at(i);

        if (param.value == name)
        {
            return i;
        }
    }

    throw "The query does not have a parameter with the name " + name;
}