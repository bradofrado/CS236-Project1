#pragma once

#include <set>
#include <string>

using namespace std;

class Node
{
private:
    set<int> adjacentNodeIDs;
public:
    void addEdge(int adjacentNodeID);
    string toString() const;
};