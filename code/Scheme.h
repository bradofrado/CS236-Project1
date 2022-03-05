#pragma once

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Scheme : public vector<string>
{
public:
	Scheme(vector<string> names) : vector<string>(names) {}

    string toString() const
    {
        stringstream ss;

        for (unsigned int i = 0; i < size(); i++)
        {
            ss << at(i) << " ";
        }
        
        return ss.str();
    }
};
