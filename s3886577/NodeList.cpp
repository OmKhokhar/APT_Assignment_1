
#include "NodeList.h"
#include <iostream>

NodeList::NodeList() {}

NodeList::NodeList(NodeList &other)
{
    this->length = other.length;
    this->nodes = new NodePtr[other.getLength()];
    for (int i = 0; i < other.getLength(); i++)
    {
        nodes[i] = new Node(*other.get(i));
    }
}

NodeList::~NodeList()
{
    clear();
}

int NodeList::getLength()
{
    return length;
}

NodePtr NodeList::get(int i)
{
    return nodes[i];
}

void NodeList::addBack(NodePtr newNode)
{
    Node **temp_nodes = new NodePtr[length];
    for (int i = 0; i < length; i++)
    {
        temp_nodes[i] = nodes[i];
    }
    this->nodes = new NodePtr[++length];
    for (int i = 0; i < this->length - 1; i++)
        this->nodes[i] = temp_nodes[i];
    this->nodes[this->length - 1] = new Node(*newNode);
    delete[] temp_nodes;
}

bool NodeList::containsNode(NodePtr node)
{
    bool ret_chk = false;
    for (int i = 0; i < this->length; ++i)
    {
        if (this->nodes[i]->getRow() == node->getRow() &&
            nodes[i]->getCol() == node->getCol())
        {
            ret_chk = true;
        }
    }
    return ret_chk;
}

NodeList *NodeList::getNodeswithDistance(int distance_from_S)
{
    NodeList *returnNodes = new NodeList();
    for (int i = 0; i < this->getLength(); i++)
    {
        if (nodes[i]->getDistanceToS() == distance_from_S)
        {
            returnNodes->addBack(new Node(*get(i)));
        }
    }
    return returnNodes;
}

void NodeList::clear()
{
    for (int i = 0; i < this->length; ++i)
    {
        delete this->nodes[i];
        this->nodes[i] = nullptr;
    }
}