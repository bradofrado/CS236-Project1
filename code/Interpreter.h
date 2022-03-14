#pragma once

#include "DatalogProgram.h"
#include "Database.h"

using namespace std;

class Interpreter
{
private:
    DatalogProgram datalogProgram;
    Database database;

    void evaluateSchemes();
    void evaluateFacts();
    void evaluateRules();
    void evaluateQueries();

    Relation evaluatePredicate(Predicate predicate, int& numResults);
    Relation evaluatePredicate(Predicate predicate);
public:
    Interpreter(DatalogProgram datalogProgram);

    void run();
};