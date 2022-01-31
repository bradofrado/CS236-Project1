#include <vector>
#include "Token.h"
#include "Parser.h"
#include <iostream>

using namespace std;

Parser::Parser(const vector<Token>& _tokens) : tokens(_tokens) {}

TokenType Parser::tokenType() const
{
    return tokens.at(0).getType();
}

void Parser::advanceToken()
{
    tokens.erase(tokens.begin());
}

void Parser::throwError()
{
    cout << "error" << endl;
}

void Parser::match(TokenType t)
{
    cout << "match: " << t << endl;

    if (tokenType() == t)
    {
        advanceToken();
    }
    else
    {
        throwError();
    }
}

void Parser::idList()
{
    if (tokenType() == COMMA)
    {
        match(COMMA);
        match(ID);
        idList();
    }
    else
    {
        //lambda
    }
}

void Parser::scheme()
{
    if (tokenType() == ID)
    {
        match(ID);
        match(LEFT_PAREN);
        match(ID);
        idList();
        match(RIGHT_PAREN);
    }
    else
    {
        throwError();
    }
}