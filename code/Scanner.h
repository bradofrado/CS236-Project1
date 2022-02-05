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

    bool charIsEqual(char c1, char c2);

    bool scanKeyword(const string& input, TokenType keyword, TokenType& type, int& size, int& lineNum);

    void scanString(const string input, TokenType& type, int& size, int& lineNum);

    void scanComment(const string& input, TokenType& type, int& size, int& lineNum);

    bool isMultiKeyWord(TokenType type);

    bool isLetter(char c);

    void scanIdentifier(const string& input, TokenType& type, int& size, int& lineNum);

    bool tryScanKeyword(const string& input, TokenType& type, int& size, int& lineNum);

public:
    Scanner(const string& input): input(input), currLineNumber(1) {}
    Token scanToken();
};