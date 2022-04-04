#include "Graph.h"
#include "Node.h"
#include <map>
#include <string>
#include <sstream>

using namespace std;

Graph::Graph(int size)
{
    for (int nodeId = 0; nodeId < size; nodeId++)
    {
        nodes[nodeId] = Node();
    }
}

void Graph::addEdge(int fromNodeId, int toNodeId)
{
    nodes[fromNodeId].addEdge(toNodeId);
}

string Graph::toString() const
{
    stringstream ss;

    for (auto& pair : nodes)
    {
        int nodeId = pair.first;
        const Node& node = pair.second;

        ss << "R" << nodeId << ":" << node.toString() << endl;
    }

    return ss.str();
}

map<int, Node>::iterator Graph::begin()
{
    return nodes.begin();
}

map<int, Node>::iterator Graph::end()
{
    return nodes.end();
}

Node& Graph::at(int index)
{
    return nodes.at(index);
}