#pragma once

#include "Rule.h"
#include <vector>
#include <stack>
#include <string>

class SCC : public vector<Rule>
{
private:
    string name;
public:
    SCC(stack<int> ids, vector<Rule> rules);
    bool isRuleDependent();

    string toString() const;
    string getName() const;
};