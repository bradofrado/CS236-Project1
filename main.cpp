#include <iostream>
#include "Token.h"
#include "Scanner.h"
using namespace std;

int main(int argc, char* argv[]) 
{
    Scanner s("Queries: marriedTo ('Bea', 'Zed')?");

    Token t;

    do
    {
        t = s.scanToken();
        cout << t.toString() << endl;
    } while (t.getType() != EOF);
}