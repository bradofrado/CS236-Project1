#pragma once

#include <string>
#include <cctype>
#include "Token.h"

using namespace std;

class Scanner 
{
private:
    string input;

    bool scanKeyword(const string& input, TokenType keyword, TokenType& type, int& size)
    {
        string keywordName = Token.typeName(keyword);
        char c;
        for (int i = 0; i < keywordName.length(); i++)
        {
            c = input.at(i);

            if (c != keywordName.at(i))
            {
                size = i;
                type = ID;
                return false;
            }
        }

        type = keyword;
        size = keywordName.length();
    }

    void scanSingleCharacter(const string& input, TokenType& type, int& size)
    {
        switch(input.at(0))
        {
            case ',':
                type = COMMA;
                size = 1;
                break;
            case '.':
                type = PERIOD;
                size = 1;
                break;
            case '?':
                type = Q_MARK;
                size = 1;
                break;
            case '(':
                type = LEFT_PAREN;
                size = 1;
                break;
            case ')':
                type = RIGHT_PAREN;
                size = 1;
                break;
            case ':':
                if (input.at(1) != '-')
                {
                    type = COLON;
                    size = 1;
                    break;
                }
                else
                {
                    type = COLOR_DASH;
                    size = 2;
                    break;
                }                
            case '*':
                type = MULTIPLY;
                size = 1;
                break;
            case '+':
                type = ADD;
                size = 1;
                break;
            case '\'':
                scanString(type, size);
                break;
            case '#':
                scanComment(type, size);
                break;
            case '':
                type = UNDEFINED;
                size = 0;
                break;
            case '':
                type = _EOF;
                size = 0;
                break;
            default:
                size = -1;
        }
    }

    void scanMultiCharacter(const string& input, TokenType& type, int& size)
    {
        TokenType keyword = UNDEFINED;
        switch (input.at(0))
        {
            case 'S':
                keyword = SCHEMES;
                break;
            case 'F':
                keyword = FACTS;
                break;
            case 'R':
                keyword = RULES;
                break;
            case 'Q':
                keyword = QUERIES;
                break;
        }  

        if (!scanKeyword(input, keyword, type, size))
        {
            keyword = UNDEFINED;
        }
    }

    void scanString(TokenType& type, int& size)
    {

    }

    void scanComment(TokenType& type, int& size)
    {

    }

    void scanIdentifier(TokenType& type, int& size)
    {

    }
public:
    Scanner(const string& input): input(input) {}
    Token scanToken()
    {
        TokenType type;
        int size = 0;

        while (isspace(input.at(0)))
        {
            input = input.substr(1);
        }

        // bool hasToken = false;
        // string currScan = "";
        // while (!hasToken)
        // {
        //     currScan += input.at(0);
        // }

        //scanSingleCharacter(input, type, size);

        // if (size == -1)
        // {
            
        // }

        bool isIdent = false;

        switch(input.at(0))
        {
            case ',':
                type = COMMA;
                size = 1;
                break;
            case '.':
                type = PERIOD;
                size = 1;
                break;
            case '?':
                type = Q_MARK;
                size = 1;
                break;
            case '(':
                type = LEFT_PAREN;
                size = 1;
                break;
            case ')':
                type = RIGHT_PAREN;
                size = 1;
                break;
            case ':':
                if (input.at(1) != '-')
                {
                    type = COLON;
                    size = 1;
                    break;
                }
                else
                {
                    type = COLOR_DASH;
                    size = 2;
                    break;
                }                
            case '*':
                type = MULTIPLY;
                size = 1;
                break;
            case '+':
                type = ADD;
                size = 1;
                break;
            case '\'':
                scanString(type, size);
                break;
            case '#':
                scanComment(type, size);
                break;
            case 'S':
                //keyword = SCHEMES;
                isIdent = scanKeyword(input, SCHEMES, type, size);
                break;
            case 'F':
                //keyword = FACTS;
                isIdent = scanKeyword(input, FACTS, type, size);
                break;
            case 'R':
                //keyword = RULES;
                isIdent = scanKeyword(input, RULES, type, size);
                break;
            case 'Q':
                //keyword = QUERIES;
                isIdent = scanKeyword(input, QUERIES, type, size);
                break;
            default:
                isIdent = true;
        }

        if (isIdent)
        {
            scanIdentifier(type, size);
        }


        string value = input.substr(0, size);
        input = input.substr(size);

        return Token(type, value, 1);
    }
};