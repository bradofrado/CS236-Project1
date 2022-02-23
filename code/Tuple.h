#pragma once

#include <vector>
#include <string>
#include "Scheme.h"

using namespace std;

class Tuple : public vector<string> 
{
public:
	Tuple(vector<string> values) : vector<string>(values) {}

    string toString(const Scheme& scheme) const;
};
