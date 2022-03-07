#pragma once

#include <vector>
#include <string>
#include "Predicate.h"

using namespace std;

class Rule
{
private:
    Predicate headPredicate;
    vector<Predicate> bodyPredicates;

public:
    Rule(Predicate& _head) : headPredicate(_head) {}
    void addPredicate(Predicate& body);
    void addPredicates(vector<Predicate> predicates);

    string toString();
};