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
    void idList();
    void scheme();
};