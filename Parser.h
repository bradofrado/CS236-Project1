#pragma once

#include <vector>
#include "Token.h"
#include "DatalogProgram.h"

class Parser 
{
private:
    bool isDebug;

    Token errorToken;
    DatalogProgram datalogObject;
    vector<Token> tokens;

    TokenType tokenType() const;
    void advanceToken();
    void throwError();
    Token match(TokenType t);

    //Grammar rules
    void datalogProgram();

    void schemeList();
    void factList();
    void ruleList();
    void queryList();

    void scheme();
    void fact();
    void rule();
    void query();

    Predicate* headPredicate();
    Predicate* predicate();

    vector<Predicate*> predicateList();
    vector<Parameter*> parameterList();
    vector<Parameter*> stringList();
    vector<Parameter*> idList();
    
    Parameter* parameter();

public:
    Parser(const vector<Token>& tokens, bool isDebug = false);
    bool parse();

    DatalogProgram getDatalogProgram();
    Token getErrorToken();
};