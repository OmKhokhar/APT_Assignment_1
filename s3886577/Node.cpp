
#include "Node.h"

Node::Node(int row, int col, int distanceToS)
{
   this->row = row;
   this->col = col;
   setDistanceToS(distanceToS);
}

Node::Node(Node &other)
{
   this->row = other.getRow();
   this->col = other.getCol();
   setDistanceToS(other.getDistanceToS());
}

Node::~Node()
{
}

int Node::getRow()
{
   return row;
}

int Node::getCol()
{
   return col;
}

int Node::getDistanceToS()
{
   return distanceToS;
}

void Node::setDistanceToS(int distanceToS)
{
   this->distanceToS = distanceToS;
}
