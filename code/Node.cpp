#include "Node.h"
#include <set>
#include <string>
#include <sstream>

using namespace std;

void Node::addEdge(int adjacentNodeID)
{
    adjacentNodeIDs.insert(adjacentNodeID);
}

string Node::toString() const
{
    stringstream ss;

    unsigned int i = 0;
    for (auto& nodeID : adjacentNodeIDs)
    {
        ss << "R" << nodeID;

        if (i < adjacentNodeIDs.size() - 1)
        {
            ss << ",";
        }

        i++;
    }

    return ss.str();
}