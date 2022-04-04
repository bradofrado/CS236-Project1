#pragma once

#include <set>
#include <string>

using namespace std;

class Node
{
private:
    set<int> adjacentNodeIDs;

    bool isMarked;
public:
    Node() : isMarked(false) {}
    
    void addEdge(int adjacentNodeID);
    string toString() const;

    bool marked();
    void mark();

    set<int>::iterator begin();
    set<int>::iterator end();
};