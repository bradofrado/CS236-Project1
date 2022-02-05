#include "Predicate.h"
#include "Parameter.h"
#include <vector>
#include <string>
#include <sstream>

using namespace std;

string Predicate::toString()
{
    stringstream ss;

    ss << name << "(";
    for (unsigned int i = 0; i < parameters.size(); i++)
    {
        ss << parameters.at(i).toString();

        if (i < parameters.size() - 1)
        {
            ss << ",";
        }
    }

    ss << ")";

    return ss.str();
}

void Predicate::addParam(Parameter param)
{
    parameters.push_back(param);
}