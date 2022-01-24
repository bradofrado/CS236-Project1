#include <iostream>
#include "Token.h"
#include "Scanner.h"
using namespace std;

int main() 
{
    Token t = Token(COMMA, ",", 2);
    cout << t.toString() << endl;

    Scanner s = Scanner(",,");
    t = s.scanToken();
    cout << t.toString() << endl;
}