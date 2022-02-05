#pragma once

#include <vector>
#include "Token.h"

class Parser 
{
private:
    vector<Token> tokens;
public: 
    Parser(const vector<Token>& tokens);
    TokenType tokenType() const;
    void advanceToken();
    void throwError();
    void match(TokenType t);

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

    void headPredicate();
    void predicate();

    void predicateList();
    void parameterList();
    void stringList();
    void idList();
    
    void parameter();
};