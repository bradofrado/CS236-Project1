#pragma once

#include <string>
#include <cctype>
#include "Token.h"

using namespace std;

class Scanner 
{
private:
    string input;
    int currLineNumber;
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

    bool scanKeyword(const string& input, TokenType keyword, TokenType& type, int& size, int& lineNum)
    {
        string keywordName = Token::typeName(keyword);
        char c;
        for (unsigned int i = 0; i < keywordName.length(); i++)
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
        currLineNumber = lineNum;

        return true;
    }

    

    void scanString(const string input, TokenType& type, int& size, int& lineNum)
    {
        if (input.at(0) != '\'')
        {
            throw std::invalid_argument("Only call scan string if this input starts with a string token");
        }

        lineNum = currLineNumber;

        unsigned int i = 1;
        while (i != input.length() && input.at(i) != '\'')
        {
            i++;

            if (i != input.length() && input.at(i) == '\n')
            {
                currLineNumber++;
            }

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

    void scanComment(const string& input, TokenType& type, int& size, int& lineNum)
    {
        lineNum = currLineNumber;

        unsigned int i = 0;
        bool multiline = false;
        while (!multiline && i != input.length() && input.at(i) != '\n')
        {
            if (input.at(i) == '|')
            {
                multiline = true;
            }
            i++;            
        }

        if (i != input.length() && input.at(i) == '\n')
        {
            currLineNumber++;
        }

        if (multiline)
        {
            while (i < input.length() - 1 && input.at(i) != '|' && input.at(i+1) != '#')
            {
                i++;

                if (input.at(i) == '\n')
                {
                    currLineNumber++;
                }
            }            

            i++;
        }

        //If we hit the end of file and 
        if (i == input.length())
        {
            if (multiline)
            {
                type = UNDEFINED;
            }            
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
        switch (type)
        {
            case QUERIES: return true;
            case SCHEMES: return true;
            case FACTS: return true;
            case RULES: return true;
            default:
                return false;
        }
    }

    bool isLetter(char c)
    {
        const int A = 65;
        const int Z = 90;
        const int a = 97;
        const int z = 122;

        int cI = (int)c;

        return (cI >= A && cI <= Z) || (cI >= a && cI <= z);
    }

    void scanIdentifier(const string& input, TokenType& type, int& size, int& lineNum)
    {
        if (!isLetter(input.at(0)))
        {
            type = UNDEFINED;
            size = 1;
            return;
        }

        unsigned int i = size;
        
        lineNum = currLineNumber;
        type = UNDEFINED;
        while (!tryScanKeyword(input.substr(i), type, size, currLineNumber) || isMultiKeyWord(type))
        {
            i++;
        }

        //Preservee the line number
        currLineNumber = lineNum;


        size = i;

        type = ID;
    }

    //Trys to scan a keyword and returns true if this was successful
    //(Essentially returns true if it is not an identifier because of the needed ispace at the bottom)
    bool tryScanKeyword(const string& input, TokenType& type, int& size, int& lineNum)
    {
        lineNum = currLineNumber;
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
                    type = COLON_DASH;
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
                scanString(input, type, size, lineNum);
                return true;
            case '#':
                scanComment(input, type, size, lineNum);
                return true;
            case 'S':
                //keyword = SCHEMES;
                return scanKeyword(input, SCHEMES, type, size, lineNum);
            case 'F':
                //keyword = FACTS;
                return scanKeyword(input, FACTS, type, size, lineNum);                
            case 'R':
                //keyword = RULES;
                return scanKeyword(input, RULES, type, size, lineNum);                
            case 'Q':
                //keyword = QUERIES;
                return scanKeyword(input, QUERIES, type, size, lineNum);                
            default:
                if (isspace(input.at(0)))
                {
                    return true;
                }
                return false;
        }
    }

public:
    Scanner(const string& input): input(input), currLineNumber(1) {}
    Token scanToken()
    {
        
        TokenType type;
        int size = 0;

        if (input.length() == 0)
        {
            return Token(_EOF, "", currLineNumber);
        }

        while (input.length() > 0 && isspace(input.at(0)))
        {
            if (input.at(0) == '\n')
            {
                currLineNumber++;
            }

            input = input.substr(1);
        }

        if (input.length() == 0)
        {
            return Token(_EOF, "", currLineNumber);
        }

        int lineNum;
        bool isIdent = !tryScanKeyword(input, type, size, lineNum);
        

        if (isIdent)
        {
            scanIdentifier(input, type, size, lineNum);
        }


        string value = input.substr(0, size);
        input = input.substr(size);

        return Token(type, value, lineNum);
    }
};