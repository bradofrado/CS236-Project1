#pragma once

#include <string>
#include <cctype>
#include "Token.h"

using namespace std;

class Scanner 
{
private:
    string input;
public:
    Scanner(const string& input): input(input) {}
    Token scanToken()
    {
        TokenType type;
        int size;

        while (isspace(input.at(0)))
        {
            input = input.substr(1);
        }

        switch(input.at(0))
        {
            case ',':
                type = COMMA;
                size = 1;
                break;
        }
        string value = input.substr(0, size);
        input = input.substr(size);

        return Token(type, value, 1);
    }
};