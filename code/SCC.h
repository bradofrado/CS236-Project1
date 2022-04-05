#pragma once

#include "Rule.h"
#include <vector>
#include <string>

class SCC : public vector<Rule>
{
private:
    string name;
public:
    SCC(string _name, vector<Rule> rules) : vector<Rule>(rules), name(_name) {}

    bool isRuleDependent();
    
    string toString() const;
    string getName() const;
};