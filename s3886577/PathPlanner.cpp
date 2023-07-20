
#include "PathPlanner.h"
#include <iostream>

PathPlanner::PathPlanner(Env env, int rows, int cols)
{
    this->env = env;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (env[i][j] == SYMBOL_START)
                this->initialPosition(i, j);
        }
    }
}

PathPlanner::~PathPlanner()
{
    delete this->reachableNodes;
    delete this->begin;
}

void PathPlanner::initialPosition(int row, int col)
{
    this->begin = new Node(row, col, 0);
}

NodeList *PathPlanner::getReachableNodes()
{
    NodeList *O = new NodeList();
    O->addBack(begin);

    NodePtr p = O->get(0);

    while (this->reachableNodes->getLength() != O->getLength())
    {
        if ((env[p->getRow() - 1][p->getCol()] == SYMBOL_EMPTY) || (env[p->getRow() - 1][p->getCol()] == SYMBOL_GOAL))
        {
            NodePtr TNode = new Node(p->getRow() + -1, p->getCol(),
                                     p->getDistanceToS() + 1);

            if (!O->containsNode(TNode))
                O->addBack(TNode);
        }

        if ((env[p->getRow()][p->getCol() + 1] == SYMBOL_EMPTY) || (env[p->getRow()][p->getCol() + 1] == SYMBOL_GOAL))
        {
            NodePtr RNode = new Node(p->getRow(), p->getCol() + 1,
                                     p->getDistanceToS() + 1);

            if (!O->containsNode(RNode))
                O->addBack(RNode);
        }

        if ((env[p->getRow() + 1][p->getCol()] == SYMBOL_EMPTY) || (env[p->getRow() + 1][p->getCol()] == SYMBOL_GOAL))
        {
            NodePtr DNode = new Node(p->getRow() + 1, p->getCol(),
                                     p->getDistanceToS() + 1);

            if (!O->containsNode(DNode))
                O->addBack(DNode);
        }

        if ((env[p->getRow()][p->getCol() - 1] == SYMBOL_EMPTY) || (env[p->getRow()][p->getCol() - 1] == SYMBOL_GOAL))
        {
            NodePtr LNode = new Node(p->getRow(), p->getCol() + -1,
                                     p->getDistanceToS() + 1);

            if (!O->containsNode(LNode))
                O->addBack(LNode);
        }

        this->reachableNodes->addBack(p);
        if (!(this->reachableNodes->getLength() == O->getLength()))
        {
            p = O->get(this->reachableNodes->getLength());
        }
    }

    return new NodeList(*O);
}

NodeList *PathPlanner::getPath()
{
    NodeList *reverseSolution = new NodeList();

    NodePtr GNode = nullptr;
    for (int i = 0; i < this->reachableNodes->getLength(); i++)
    {
        if (env[this->reachableNodes->get(i)->getRow()][this->reachableNodes->get(i)->getCol()] == SYMBOL_GOAL)
        {
            GNode = new Node(*this->reachableNodes->get(i));
        }
    }
    reverseSolution->addBack(new Node(*GNode));

    int distance_from_S = reverseSolution->get(reverseSolution->getLength() - 1)->getDistanceToS();

    for (int i = distance_from_S - 1; i >= 0; --i)
    {
        bool chk = false;
        NodeList *nodesAtDistance = this->reachableNodes->getNodeswithDistance(i);

        for (int j = 0; j < nodesAtDistance->getLength(); j++)
        {
            int curr_row = reverseSolution->get(reverseSolution->getLength() - 1)->getRow();
            int curr_col = reverseSolution->get(reverseSolution->getLength() - 1)->getCol();

            if (curr_row - nodesAtDistance->get(j)->getRow() == 1 && curr_col == nodesAtDistance->get(j)->getCol() && !chk)
            {
                NodePtr node = new Node(*nodesAtDistance->get(j));
                if (!reverseSolution->containsNode(node))
                {
                    reverseSolution->addBack(new Node(*node));
                    chk = true;
                }
                delete node;
            }

            if (curr_col - nodesAtDistance->get(j)->getCol() == -1 && curr_row == nodesAtDistance->get(j)->getRow() && !chk)
            {
                NodePtr node = new Node(*nodesAtDistance->get(j));
                if (!reverseSolution->containsNode(node))
                {
                    reverseSolution->addBack(new Node(*node));
                    chk = true;
                }
                delete node;
            }

            if (curr_row - nodesAtDistance->get(j)->getRow() == -1 && curr_col == nodesAtDistance->get(j)->getCol() && !chk)
            {
                NodePtr node = new Node(*nodesAtDistance->get(j));
                if (!reverseSolution->containsNode(node))
                {
                    reverseSolution->addBack(new Node(*node));
                    chk = true;
                }
                delete node;
            }

            if (curr_col - nodesAtDistance->get(j)->getCol() == 1 && curr_row == nodesAtDistance->get(j)->getRow() && !chk)
            {
                NodePtr node = new Node(*nodesAtDistance->get(j));
                if (!reverseSolution->containsNode(node))
                {
                    reverseSolution->addBack(new Node(*node));
                    chk = true;
                }
                delete node;
            }
        }
        delete nodesAtDistance;
    }
    return new NodeList(*reverseSolution);
}
