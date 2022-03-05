#include "Predicate.h"
#include "Parameter.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

string Predicate::toString()
{
    stringstream ss;

    ss << name << "(";
    for (unsigned int i = 0; i < parameters.size(); i++)
    {
        ss << parameters.at(i)->toString();

        if (i < parameters.size() - 1)
        {
            ss << ",";
        }
    }

    ss << ")";

    return ss.str();
}

void Predicate::addParam(Parameter* param)
{
    parameters.push_back(param);
}

void Predicate::addParams(vector<Parameter*> params)
{
    for (unsigned int i = 0; i < params.size(); i++)
    {
        parameters.push_back(params.at(i));
    }
}

vector<string> Predicate::getParamNames() const
{
    vector<string> names;
    for (auto& param : parameters)
    {
        names.push_back(param->value);
    }

    return names;
}

string Predicate::getName() const
{
    return name;
}