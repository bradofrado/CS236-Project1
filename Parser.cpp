#include <vector>
#include "Token.h"
#include "Parser.h"
#include <iostream>

using namespace std;

Parser::Parser(const vector<Token>& _tokens) : tokens(_tokens) {}

DatalogProgram Parser::parse() 
{
    datalogProgram();

    return datalogObject;
}

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
    Token token = tokens.at(0);
    cout << "error: " << token.toString() << endl;
}

void Parser::match(TokenType t)
{
    cout << "matching: " << tokens.at(0).toString() << " with " << Token::typeName(t) << endl;

    if (tokenType() == t)
    {
        advanceToken();
    }
    else
    {
        throwError();
    }
}

void Parser::datalogProgram()
{
    if (tokenType() == SCHEMES)
    {
        match(SCHEMES);
        match(COLON);
        scheme();
        schemeList();
        match(FACTS);
        match(COLON);
        factList();
        match(RULES);
        match(COLON);
        ruleList();
        match(QUERIES);
        match(COLON);
        query();
        queryList();
        match(_EOF);
    }
    else
    {
        throwError();
    }
}

void Parser::schemeList()
{
    if (tokenType() == ID)
    {
        scheme();
        schemeList();
    }
    else
    {
        //lambda
    }
}
void Parser::factList()
{
    if (tokenType() == ID)
    {
        fact();
        factList();
    }
    else
    {
        //lambda
    }
}
void Parser::ruleList()
{
    if (tokenType() == ID)
    {
        rule();
        ruleList();
    }
    else
    {
        //lambda
    }
}
void Parser::queryList()
{
    if (tokenType() == ID)
    {
        query();
        queryList();
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
void Parser::fact()
{
    if (tokenType() == ID)
    {
        match(ID);
        match(LEFT_PAREN);
        match(STRING);
        stringList();
        match(RIGHT_PAREN);
        match(PERIOD);
    }
    else
    {
        throwError();
    }
}
void Parser::rule()
{
    if (tokenType() == ID)
    {
        headPredicate();
        match(COLON_DASH);
        predicate();
        predicateList();
        match(PERIOD);
    }
    else
    {
        throwError();
    }
}
void Parser::query()
{
    if (tokenType() == ID)
    {
        predicate();
        match(Q_MARK);
    }
    else
    {
        throwError();
    }
}

void Parser::headPredicate()
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
void Parser::predicate()
{
    if (tokenType() == ID)
    {
        match(ID);
        match(LEFT_PAREN);
        parameter();
        parameterList();
        match(RIGHT_PAREN);
    }
    else
    {
        throwError();
    }
}

void Parser::predicateList()
{
    if (tokenType() == COMMA)
    {
        match(COMMA);
        predicate();
        predicateList();        
    }
    else
    {
        //lambda
    }
}
void Parser::parameterList()
{
    if (tokenType() == COMMA)
    {
        match(COMMA);
        parameter();
        parameterList();
    }
    else
    {
        //lambda
    }
}
void Parser::stringList()
{
    if (tokenType() == COMMA)
    {
        match(COMMA);
        match(STRING);
        stringList();
    }
    else
    {
        //lambda
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
    
void Parser::parameter()
{
    if (tokenType() == STRING)
    {
        match(STRING);
    }
    else if (tokenType() == ID)
    {
        match(ID);
    }
    else
    {
        throwError();
    }
}