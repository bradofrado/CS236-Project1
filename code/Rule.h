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

    vector<Predicate> getBodyPredicates() const;
    Predicate getHeadPredicate() const;

    string getName() const;

    string toString();
};