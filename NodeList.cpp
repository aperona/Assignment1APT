#include "NodeList.h"
#include <iostream>

NodeList::NodeList() :

                       length(0)
{
}

NodeList::~NodeList()
{
    //deleting the nodes
    for (int x = 0; x < length; ++x)
    {
        delete nodes[length];
    }
}

NodeList::NodeList(NodeList &other)
{
    //copying the nodes
    for (int x = 0; x < length; ++x)
    {
        other.nodes[x] = nodes[x];
    }
}

int NodeList::getLength()
{
    return length;
}

void NodeList::addElement(Node *newPos)
{

    nodes[length] = newPos;
    ++length;
}

Node *NodeList::getNode(int i)
{

    return nodes[i];
}