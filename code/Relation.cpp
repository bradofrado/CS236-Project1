#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <map>

#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"

using namespace std;


Relation::Relation(const string& name, const Scheme& scheme, set<Tuple> tuples) : name(name), scheme(scheme)
{
    for (auto& tuple : tuples) 
    {
        addTuple(tuple);
    }   
}

void Relation::addTuple(const Tuple& tuple) {
    if (tuple.size() != scheme.size()) {
        throw invalid_argument("Tuple must have the same size as the scheme");
    }

    tuples.insert(tuple);
}

string Relation::toString() const {
    stringstream out;
    unsigned int i = 0;
    for (auto& tuple : tuples) {
        out << "  " << tuple.toString(scheme);
        i++;

        if (i < tuples.size())
        {
            out << endl;
        }
    }
    return out.str();
}

string Relation::getName() const
{
    return name;
}

vector<string> Relation::getSchemeNames() const
{
    return scheme;
}

void Relation::setName(string name)
{
    this->name = name;
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
        throw invalid_argument("No positions");
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

Relation Relation::project(vector<string> columns) const
{
    vector<int> columnIndexes;
    // for (unsigned int i = 0; i < scheme.size(); i++) 
    // {
    //     for (string column : columns)
    //     {
    //         if (scheme.at(i) == column)
    //         {
    //             columnIndexes.push_back(i);
    //         }
    //     }
    // }

    for (string column : columns) 
    {
        for (unsigned int i = 0; i < scheme.size(); i++)
        {
            if (scheme.at(i) == column)
            {
                columnIndexes.push_back(i);
            }
        }
    }

    return project(columnIndexes);
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
            throw invalid_argument("All the indexes must map to a column in this scheme");
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
        throw invalid_argument("The rename map must have the same size as this scheme");
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

    Scheme newScheme = joinSchemes(leftScheme, rightScheme);

    Relation result(name, newScheme);

    for (const Tuple& leftTuple : tuples) 
    {
        for (const Tuple& rightTuple : r.tuples) 
        {
            if (joinable(leftScheme, rightScheme, leftTuple, rightTuple))
            {
                Tuple tuple = result.joinTuples(leftTuple, rightTuple);
                result.addTuple(tuple);
            }
        }
    }

    return result;
}

Relation Relation::Union(const Relation& r)
{
    invalid_argument exception("The relations " + name + " and " + r.name + " are not union compatible");

    if (r.scheme.size() != scheme.size())
    {
        throw exception;
    }

    //Make sure the scheme names are the same
    for (unsigned int i = 0; i < scheme.size(); i++)
    {
        if (scheme.at(i) != r.scheme.at(i))
        {
            throw exception;
        }
    }

    Relation result(name, scheme, tuples);

    for (Tuple tuple : r.tuples)
    {
        result.addTuple(tuple);
    }

    return result;
}

Scheme Relation::joinSchemes(const Scheme& leftScheme, const Scheme& rightScheme)
{
    vector<string> names;
    for (string leftName : leftScheme) 
    {
        bool isSame = false;
        for (string rightName : rightScheme)
        {
            if (leftName == rightName)
            {
                isSame = true;
                break;
            }
        }

        if (!isSame)
        {
            names.push_back(leftName);
        }
    }

    for (string rightName : rightScheme) 
    {
        bool isSame = false;
        for (string leftName : leftScheme)
        {
            if (rightName == leftName)
            {
                isSame = true;
                break;
            }
        }

        if (!isSame)
        {
            names.push_back(rightName);
        }
    }

    return Scheme(names);
}

Tuple Relation::joinTuples(const Tuple& leftTuple, const Tuple& rightTuple)
{
    vector<string> values;
    for (string leftValue : leftTuple) 
    {
        bool isSame = false;
        for (string rightValue : rightTuple)
        {
            if (leftValue == rightValue)
            {
                isSame = true;
                break;
            }
        }

        if (!isSame)
        {
            values.push_back(leftValue);
        }
    }

    for (string rightValue : rightTuple) 
    {
        bool isSame = false;
        for (string leftValue : leftTuple)
        {
            if (rightValue == leftValue)
            {
                isSame = true;
                break;
            }
        }

        if (!isSame)
        {
            values.push_back(rightValue);
        }
    }

    if (scheme.size() != values.size())
    {
        throw runtime_error("Something went wrong with combining these tuples: " + leftTuple.toString(scheme) + rightTuple.toString(scheme));
    }

    return Tuple(values);
}

bool Relation::joinable (const Scheme& leftScheme, const Scheme& rightScheme,
		       const Tuple& leftTuple, const Tuple& rightTuple)
{
    for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
        const string& leftName = leftScheme.at(leftIndex);
        const string& leftValue = leftTuple.at(leftIndex);
        
        for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
            const string& rightName = rightScheme.at(rightIndex);
            const string& rightValue = rightTuple.at(rightIndex);
            
            if (rightName == leftName && rightValue != leftValue)
            {
                return false;
            }
        }
    }

    

    return true;
}
