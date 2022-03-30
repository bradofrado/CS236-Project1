#pragma once

#include <vector>
#include <string>
#include "Parameter.h"

using namespace std;

class Predicate
{
private:
    string name;
    vector<Parameter> parameters;
public:
    Predicate(string _name) : name(_name) {}
    string toString() const;

    void addParam(Parameter& param);
    void addParams(vector<Parameter> params);

    vector<Parameter> getParams() const;
    vector<string> getParamNames() const;
    string getName() const;
};