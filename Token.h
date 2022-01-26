#pragma once
#include <string>
#include <sstream>

using namespace std;

enum TokenType {
    COMMA, 
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    _EOF
};

class Token
{
private:
    TokenType type;
    string value;
    int line;
public:
    Token(TokenType _type, string _value, int _line) : type(_type), value(_value), line(_line) {}
    Token(){}

    string toString() const;

    TokenType getType();

    static string typeKeyword(TokenType type);

    static string typeName(TokenType type);
};