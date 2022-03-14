#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <map>

#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"

using namespace std;


Relation::Relation(const Relation& relation) : name(relation.name), scheme(relation.scheme)
{
    for (auto& tuple : relation.tuples) 
    {
        addTuple(tuple);
    }   
}

void Relation::addTuple(const Tuple& tuple) {
    if (tuple.size() != scheme.size()) {
        throw "Tuple must have the same size as the scheme";
    }

    tuples.insert(tuple);
}

string Relation::toString() const {
    stringstream out;
    for (auto& tuple : tuples)
        out << "  " << tuple.toString(scheme) << endl;
    return out.str();
}

string Relation::getName() const
{
    return name;
}

int Relation::size() const
{
    return tuples.size();
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
            int curr = positions[i];
            if (tuple.at(curr) != tuple.at(first))
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

Relation Relation::project(vector<int> columns) const
{
    vector<string> schemeNames;
    Scheme newScheme(schemeNames);
    Relation result(name, newScheme);

    //If there is nothing to project, return an empty relation
    if (columns.size() == 0)
    {
        return result;
    }

    //Make the new scheme with the projected columns
    for (auto& index : columns)
    {
        if (index >= (int)scheme.size())
        {
            throw "All the indexes must map to a column in this scheme";
        }

        result.scheme.push_back(scheme.at(index));
    }

    //Loop through the tuples and with the new columns
    for (auto& tuple : tuples)
    {
        vector<string> values;
        Tuple newTuple(values);
        for (auto& index : columns)
        {
            newTuple.push_back(tuple.at(index));
        }

        result.addTuple(newTuple);
    }

    return result;
}

Relation Relation::rename(vector<string> newNames) const
{
    if (newNames.size() != scheme.size())
    {
        throw "The rename map must have the same size as this scheme";
    }

    Relation result(*this);

    for (unsigned int i = 0; i < newNames.size(); i++)
    {
        string name = newNames.at(i);
        result.scheme.at(i) = name;
    }

    return result;
}

Relation Relation::join(const Relation& r)
{
    const Scheme& leftScheme = scheme;
    const Scheme& rightScheme = r.scheme;

    for (const Tuple& leftTuple : tuples) {
        cout << "left tuple: " << leftTuple.toString(leftScheme) << endl;

        for (const Tuple& rightTuple : r.tuples) {
            cout << "right tuple: " << rightTuple.toString(rightScheme) << endl;
        }
    }

    return Relation(name, scheme);
}

bool Relation::joinable (const Scheme& leftScheme, const Scheme& rightScheme,
		       const Tuple& leftTuple, const Tuple& rightTuple)
{
    for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
        const string& leftName = leftScheme.at(leftIndex);
        const string& leftValue = leftTuple.at(leftIndex);
        cout << "left name: " << leftName << " value: " << leftValue << endl;

        for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
            const string& rightName = rightScheme.at(rightIndex);
            const string& rightValue = rightTuple.at(rightIndex);
            cout << "right name: " << rightName << " value: " << rightValue << endl;

            if (rightName == leftName && rightValue != leftValue)
            {
                return false;
            }
        }
    }

    

    return true;
}
