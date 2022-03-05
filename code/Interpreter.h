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
public:
    Interpreter(DatalogProgram datalogProgram);

    void run();
};