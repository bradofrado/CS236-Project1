#include <vector>
#include <string>
#include <sstream>
#include "Predicate.h"
#include "Rule.h"
#include "DatalogProgram.h"

using namespace std;

string DatalogProgram::toString()
{
    stringstream ss;

    ss << "Schemes(" << schemes.size() << "):" << endl;
    for (unsigned int i = 0; i < schemes.size(); i++)
    {
        ss << "\t" << schemes.at(i).toString() << endl;
    }

    ss << "Facts(" << facts.size() << "):" << endl;
    for (unsigned int i = 0; i < facts.size(); i++)
    {
        ss << "\t" << facts.at(i).toString() << endl;
    }

    ss << "Rules(" << rules.size() << "):" << endl;
    for (unsigned int i = 0; i < rules.size(); i++)
    {
        ss << "\t" << rules.at(i).toString() << endl;
    }

    ss << "Queries(" << queries.size() << "):" << endl;
    for (unsigned int i = 0; i < queries.size(); i++)
    {
        ss << "\t" << queries.at(i).toString() << endl;
    }

    ss << "Domain(" << domain.size() << "):" << endl;
    for (set<string>::iterator i = domain.begin(); i != domain.end(); i++)
    {
        ss << "\t" << *i << endl;
    }
}

set<string> DatalogProgram::getDomain() const
{
    return domain;
}

vector<Predicate> DatalogProgram::getSchemes() const
{
    return schemes;
}

vector<Predicate> DatalogProgram::getFacts() const
{
    return facts;
}

vector<Rule> DatalogProgram::getRules() const
{
    return rules;
}   

vector<Predicate> DatalogProgram::getQueries() const
{
    return queries;
}


void DatalogProgram::addDomain(string _domain)
{
    domain.insert(_domain);
}

void DatalogProgram::addSchemes(Predicate scheme)
{
    schemes.push_back(scheme);
}

void DatalogProgram::addFacts(Predicate fact)
{
    facts.push_back(fact);
}

void DatalogProgram::addQueries(Predicate query)
{
    queries.push_back(query);
}

void DatalogProgram::addRules(Rule rule)
{
    rules.push_back(rule);
}
