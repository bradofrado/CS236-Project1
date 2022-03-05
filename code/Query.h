#pragma once

#include <vector>
#include <string>
#include <map>
#include "Parameter.h"

class Query : public vector<Parameter>
{
public:
    Query(vector<Parameter> params) : vector(params) {}
    vector<int> getConstants();
    map<string, vector<int>> getVariables();
};