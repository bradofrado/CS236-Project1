#pragma once

#include <set>
#include <vector>
#include <string>
#include "Predicate.h"
#include "Rule.h"

using namespace std;

class DatalogProgram
{
private:
    set<string> domain;
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;

public:
    DatalogProgram();
    
    set<string> getDomain() const;
    vector<Predicate> getSchemes() const;
    vector<Predicate> getFacts() const;
    vector<Rule> getRules() const;
    vector<Predicate> getQueries() const;

    void addDomain(string domain);
    void addSchemes(Predicate scheme);
    void addFacts(Predicate fact);
    void addQueries(Predicate query);
    void addRules(Rule rule);
    
    string toString();
};