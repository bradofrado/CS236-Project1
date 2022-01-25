#pragma once

#include <string>
#include <cctype>
#include "Token.h"

using namespace std;

class Scanner 
{
private:
    string input;
    
    //Compares if two chars are equal ignoring case
    bool charIsEqual(char c1, char c2)
    {
        int cI1 = (int)c1;
        int cI2 = (int)c2;

        if (!isLetter(c1) && !isLetter(c2))
        {
            return cI1 == cI2;
        }

        //If they are letters, make them both upper case
        cI1 = cI1 > 90 ? cI1 - 32 : cI1;
        cI2 = cI2 > 90 ? cI2 - 32 : cI2;

        return cI1 == cI2;
    }

    bool scanKeyword(const string& input, TokenType keyword, TokenType& type, int& size)
    {
        string keywordName = Token::typeName(keyword);
        char c;
        for (int i = 0; i < keywordName.length(); i++)
        {
            c = input.at(i);

            if (!charIsEqual(c, keywordName.at(i)))
            {
                size = i;
                type = ID;
                return false;
            }
        }

        type = keyword;
        size = keywordName.length();

        return true;
    }

    

    void scanString(const string input, TokenType& type, int& size)
    {
        if (input.at(0) != '\'')
        {
            throw std::invalid_argument("Only call scan string if this input starts with a string token");
        }

        int i = 1;
        while (input.at(i) != '\'' && i != input.length())
        {
            i++;

            if (i < input.length() -1 && input.at(i) == '\'' && input.at(i+1) == '\'')
            {
                i += 2;
            }
        }

        //If we hit the end of file and 
        if (i == input.length())
        {
            type = UNDEFINED;
        }
        else
        {
            i++;
            type = STRING;
        }

        size = i;
    }

    void scanComment(const string input, TokenType& type, int& size)
    {
        int i = 0;
        bool multiline = false;
        while (!multiline && input.at(i) != '\n' && i != input.length())
        {
            if (input.at(i) == '|')
            {
                multiline = true;
            }
            i++;            
        }

        if (multiline)
        {
            while (i < input.length() - 1 && input.at(i) != '|' && input.at(i+1) != '#')
            {
                i++;
            }

            i++;
        }

        //If we hit the end of file and 
        if (i == input.length())
        {
            type = UNDEFINED;
        }
        else
        {
            i++;
            type = COMMENT;
        }

        size = i;
    }

    bool isMultiKeyWord(TokenType type)
    {
        return Token::typeName(type).length() > 1 && type != COLOR_DASH;
    }

    bool isLetter(char c)
    {
        const int A = 65;
        const int Z = 90;
        const int a = 97;
        const int z = 122;

        int cI = (int)c;

        return cI >= A && cI <= Z || cI >= a && cI <= z;
    }

    void scanIdentifier(const string& input, TokenType& type, int& size)
    {
        if (!isLetter(input.at(0)))
        {
            type = UNDEFINED;
            size = 1;
            return;
        }

        bool isKeyword = false;
        int i = size;
        
        while (!tryScanKeyword(input.substr(i), type, size) && !isMultiKeyWord(type))
        {
            i++;
        }

        size = i;

        type = ID;
    }

    //Trys to scan a keyword and returns true if this was successful
    //(Essentially returns true if it is not an identifier because of the needed ispace at the bottom)
    bool tryScanKeyword(const string& input, TokenType& type, int& size)
    {
        switch(input.at(0))
        {
            case ',':
                type = COMMA;
                size = 1;
                return true;
            case '.':
                type = PERIOD;
                size = 1;
                return true;
            case '?':
                type = Q_MARK;
                size = 1;
                return true;
            case '(':
                type = LEFT_PAREN;
                size = 1;
                return true;
            case ')':
                type = RIGHT_PAREN;
                size = 1;
                return true;
            case ':':
                if (input.at(1) != '-')
                {
                    type = COLON;
                    size = 1;                    
                }
                else
                {
                    type = COLOR_DASH;
                    size = 2;                    
                } 
                return true;               
            case '*':
                type = MULTIPLY;
                size = 1;
                return true;
            case '+':
                type = ADD;
                size = 1;
                return true;
            case '\'':
                scanString(input, type, size);
                return true;
            case '#':
                scanComment(input, type, size);
                return true;
            case 'S':
                //keyword = SCHEMES;
                return scanKeyword(input, SCHEMES, type, size);
            case 'F':
                //keyword = FACTS;
                return scanKeyword(input, FACTS, type, size);                
            case 'R':
                //keyword = RULES;
                return scanKeyword(input, RULES, type, size);                
            case 'Q':
                //keyword = QUERIES;
                return scanKeyword(input, QUERIES, type, size);                
            default:
                if (isspace(input.at(0)))
                {
                    return true;
                }
                return false;
        }
    }

public:
    Scanner(const string& input): input(input) {}
    Token scanToken()
    {
        
        TokenType type;
        int size = 0;

        if (input.length() == 0)
        {
            return Token(_EOF, "", 1);
        }

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

        bool isIdent = !tryScanKeyword(input, type, size);
        

        if (isIdent)
        {
            scanIdentifier(input, type, size);
        }


        string value = input.substr(0, size);
        input = input.substr(size);

        return Token(type, value, 1);
    }
};