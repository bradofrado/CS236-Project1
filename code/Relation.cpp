#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"

using namespace std;

void Relation::addTuple(const Tuple& tuple) {
    tuples.insert(tuple);
}

string Relation::toString() const {
    stringstream out;
    for (auto& tuple : tuples)
        out << tuple.toString(scheme) << endl;
    return out.str();
}

Relation Relation::select(int index, const string& value) const {
    Relation result(name, scheme);
    for (auto& tuple : tuples)
        if (tuple.at(index) == value)
    result.addTuple(tuple);
    return result;
}