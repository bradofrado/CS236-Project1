#pragma once

#include <string>

using namespace std;

struct Parameter
{
    Parameter(string _value, bool _isId) : value(_value), isId(_isId) {}
    string value;
    bool isId;
    
    string toString() const;
};