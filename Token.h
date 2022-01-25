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

    string toString() const 
    {
        stringstream out;
        out << "(" << typeName(type) << "," << "\"" << value << "\"" << "," << line << ")";

        return out.str();
    }

    TokenType getType()
    {
        return type;
    }

    static string typeKeyword(TokenType type)
    {
        switch(type)
        {
            case COMMA:
                return "Comma";
            case PERIOD:
                return ".";
            case Q_MARK:
                return "?";
            case LEFT_PAREN:
                return "(";
            case RIGHT_PAREN:
                return ")";
            case COLON:
                return ":";
            case COLON_DASH:
                return ":-";
            case MULTIPLY:
                return "*";
            case ADD:
                return "+";
            case SCHEMES:
                return "Schemes";
            case FACTS:
                return "Facts";
            case RULES:
                return "Rules";
            case QUERIES:
                return "Queries";
            case ID:
                return "ID";
            case STRING:
                return "\'";
            case COMMENT:
                return "#";
            case UNDEFINED:
                return "UNDEFINED";
            case _EOF:
                return "EOF";
            default:
                return "";
        }
    }

    static string typeName(TokenType type)
    {
        switch(type)
        {
            case COMMA:
                return "COMMA";
            case PERIOD:
                return "PERIOD";
            case Q_MARK:
                return "Q_MARK";
            case LEFT_PAREN:
                return "LEFT_PAREN";
            case RIGHT_PAREN:
                return "RIGHT_PAREN";
            case COLON:
                return "COLON";
            case COLON_DASH:
                return "COLON_DASH";
            case MULTIPLY:
                return "MULTIPLY";
            case ADD:
                return "ADD";
            case SCHEMES:
                return "SCHEMES";
            case FACTS:
                return "FACTS";
            case RULES:
                return "RULES";
            case QUERIES:
                return "QUERIES";
            case ID:
                return "ID";
            case STRING:
                return "STRING";
            case COMMENT:
                return "COMMENT";
            case UNDEFINED:
                return "UNDEFINED";
            case _EOF:
                return "EOF";
            default:
                return "";
        }
    }
};