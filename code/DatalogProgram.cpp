#include <vector>
#include <string>
#include <sstream>
#include "Predicate.h"
#include "Rule.h"
#include "DatalogProgram.h"

using namespace std;

DatalogProgram::DatalogProgram()
{
    
}

string DatalogProgram::toString()
{
    stringstream ss;

    ss << "Schemes(" << schemes.size() << "):" << endl;
    for (unsigned int i = 0; i < schemes.size(); i++)
    {
        ss << "  " << schemes.at(i)->toString() << endl;
    }

    ss << "Facts(" << facts.size() << "):" << endl;
    for (unsigned int i = 0; i < facts.size(); i++)
    {
        ss << "  " << facts.at(i)->toString() << "." << endl;
    }

    ss << "Rules(" << rules.size() << "):" << endl;
    for (unsigned int i = 0; i < rules.size(); i++)
    {
        ss << "  " << rules.at(i)->toString() << "." << endl;
    }

    ss << "Queries(" << queries.size() << "):" << endl;
    for (unsigned int i = 0; i < queries.size(); i++)
    {
        ss << "  " << queries.at(i)->toString() << "?" << endl;
    }

    ss << "Domain(" << domain.size() << "):" << endl;
    for (set<string>::iterator i = domain.begin(); i != domain.end(); i++)
    {
        ss << "  " << *i << endl;
    }

    return ss.str();
}

set<string> DatalogProgram::getDomain() const
{
    return domain;
}

vector<Predicate*> DatalogProgram::getSchemes() const
{
    return schemes;
}

vector<Predicate*> DatalogProgram::getFacts() const
{
    return facts;
}

vector<Rule*> DatalogProgram::getRules() const
{
    return rules;
}   

vector<Predicate*> DatalogProgram::getQueries() const
{
    return queries;
}


void DatalogProgram::addDomain(Parameter* _domain)
{
    domain.insert(_domain->value);
}

void DatalogProgram::addDomains(vector<Parameter*> _domains)
{
    for (unsigned int i = 0; i < _domains.size(); i++)
    {
        domain.insert(_domains.at(i)->value);
    }
}

void DatalogProgram::addScheme(Predicate* scheme)
{
    schemes.push_back(scheme);
}

void DatalogProgram::addFact(Predicate* fact)
{
    facts.push_back(fact);
}

void DatalogProgram::addQuerie(Predicate* query)
{
    queries.push_back(query);
}

void DatalogProgram::addRule(Rule* rule)
{
    rules.push_back(rule);
}
