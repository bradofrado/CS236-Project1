#include <vector>
#include "Token.h"
#include "Parser.h"
#include <iostream>

using namespace std;

Parser::Parser(const vector<Token>& _tokens) : tokens(_tokens) 
{

}

bool Parser::parse() 
{
    datalogProgram();

    return true;
}

DatalogProgram Parser::getDatalogProgram()
{
    return datalogObject;
}

Token Parser::getErrorToken()
{
    
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

Token Parser::match(TokenType t)
{
    cout << "matching: " << tokens.at(0).toString() << " with " << Token::typeName(t) << endl;

    if (tokenType() == t)
    {
        Token token = tokens.at(0);
        advanceToken();

        return token;
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
        Token schemeId = match(ID);
        Predicate* scheme = new Predicate(schemeId.getValue());
        datalogObject.addScheme(scheme);
        
        match(LEFT_PAREN);
        Token paramId = match(ID);
        Parameter* param = new Parameter(paramId.getValue(), true);
        scheme->addParam(param);

        vector<Parameter*> params = idList();
        scheme->addParams(params);

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
        Token factId = match(ID);
        Predicate* fact = new Predicate(factId.getValue());
        
        match(LEFT_PAREN);
        Token paramId = match(STRING);
        Parameter* param = new Parameter(paramId.getValue(), false);
        fact->addParam(param);

        vector<Parameter*> params = stringList();
        fact->addParams(params);

        datalogObject.addDomain(param);
        datalogObject.addDomains(params);
        datalogObject.addFact(fact);

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
        Predicate* head = headPredicate();
        match(COLON_DASH);
        Predicate* first = predicate();
        vector<Predicate*> rest = predicateList();
        match(PERIOD);

        Rule* rule = new Rule(head);
        rule->addPredicate(first);
        rule->addPredicates(rest);

        datalogObject.addRule(rule);
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
        Predicate* query = predicate();
        match(Q_MARK);

        datalogObject.addQuerie(query);
    }
    else
    {
        throwError();
    }
}

Predicate* Parser::headPredicate()
{
    if (tokenType() == ID)
    {
        Token predicateId = match(ID);
        Predicate* predicate = new Predicate(predicateId.getValue());
        
        match(LEFT_PAREN);
        Token paramId = match(ID);
        Parameter* param = new Parameter(paramId.getValue(), true);
        predicate->addParam(param);

        vector<Parameter*> params = idList();
        predicate->addParams(params);

        match(RIGHT_PAREN);

        return predicate;
    }
    else
    {
        throwError();
    }
}
Predicate* Parser::predicate()
{
    if (tokenType() == ID)
    {
        // match(ID);
        // match(LEFT_PAREN);
        // parameter();
        // parameterList();
        // match(RIGHT_PAREN);

        Token predicateId = match(ID);
        Predicate* predicate = new Predicate(predicateId.getValue());
        
        match(LEFT_PAREN);
        Parameter* param = parameter();
        predicate->addParam(param);

        vector<Parameter*> params = parameterList();
        predicate->addParams(params);

        match(RIGHT_PAREN);

        return predicate;
    }
    else
    {
        throwError();
    }
}

vector<Predicate*> Parser::predicateList()
{
    if (tokenType() == COMMA)
    {
        match(COMMA);
        Predicate* first = predicate();
        vector<Predicate*> rest = predicateList(); 

        rest.insert(rest.begin(), first);

        return rest;       
    }
    else
    {
        //lambda
        vector<Predicate*> preds;
        return preds;
    }
}
vector<Parameter*> Parser::parameterList()
{
    if (tokenType() == COMMA)
    {
        // match(COMMA);
        // parameter();
        // parameterList();

        match(COMMA);
        
        Parameter* param = parameter();
        vector<Parameter*> params = parameterList();
        params.insert(params.begin(), param);

        return params;
    }
    else
    {
        vector<Parameter*> params;
        return params;
    }
}
vector<Parameter*> Parser::stringList()
{
    if (tokenType() == COMMA)
    {
        match(COMMA);
        Token paramId = match(STRING);
        Parameter* param = new Parameter(paramId.getValue(), false);

        vector<Parameter*> params = stringList();
        params.insert(params.begin(), param);

        return params;
    }
    else
    {
        //lambda
        vector<Parameter*> params;
        return params;
    }   
}
vector<Parameter*> Parser::idList()
{
    if (tokenType() == COMMA)
    {
        match(COMMA);
        Token paramId = match(ID);
        Parameter* param = new Parameter(paramId.getValue(), true);

        vector<Parameter*> params = idList();
        params.insert(params.begin(), param);

        return params;
    }
    else
    {
        //lambda
        vector<Parameter*> params;
        return params;
    }
}
    
Parameter* Parser::parameter()
{
    if (tokenType() == STRING)
    {
        Token paramId = match(STRING);
        Parameter* param = new Parameter(paramId.getValue(), false);
        return param;
    }
    else if (tokenType() == ID)
    {
        Token paramId = match(ID);
        Parameter* param = new Parameter(paramId.getValue(), true);
        return param;
    }
    else
    {
        throwError();
    }
}