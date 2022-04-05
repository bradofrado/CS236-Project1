#include "SCC.h"
#include <string>

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