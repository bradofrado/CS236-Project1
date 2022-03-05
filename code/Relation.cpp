#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"

using namespace std;

void Relation::addTuple(const Tuple& tuple) {
    if (tuple.size() != scheme.size()) {
        throw "Tuple must have the same size as the scheme";
    }

    tuples.insert(tuple);
}

string Relation::toString() const {
    stringstream out;
    out << scheme.toString() << endl;

    for (auto& tuple : tuples)
        out << tuple.toString(scheme) << endl;
    return out.str();
}

Relation Relation::select(int index, const string& value) const {
    Relation result(name, scheme);
    for (auto& tuple : tuples)
        if (tuple.at(index) == value) {
            result.addTuple(tuple);
        }
    return result;
}

Relation Relation::select(vector<int> positions) const
{
    if (positions.size() == 0)
    {
        throw "No positions";
    }

    Relation result(name, scheme);
    for (auto& tuple : tuples) {
        int first = positions[0];
        bool isEqual = true;
        for (unsigned int i = 1; i < positions.size(); i++)
        {
            if (tuple.at(i) != tuple.at(first))
            {
                isEqual = false;
                break;
            }
        }

        if (isEqual)
        {
            result.addTuple(tuple);
        }
    }

    return result;
}

string Relation::getName() const
{
    return name;
}