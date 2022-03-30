#pragma once

#include <map>
#include <string>

#include "Node.h"

using namespace std;

class Graph
{
private:
    map<int, Node> nodes;

public:
    Graph(int size);

    void addEdge(int fromNodeID, int toNodeID);
    string toString() const;
};