#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"

Env make_env(const int row, const int column);

void delete_env(Env env, int row, int column);

void printReachablePositions(NodeList *reachablePositions);

// Read a environment from standard input.
void readEnvStdin(Env &env, int &row, int &column);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printPath(Env env, int &row, int &column, NodeList *solution);

int main(void)
{
    int row;
    int column;
    Env env;
    readEnvStdin(env, row, column);

    PathPlanner *pathplanner = new PathPlanner(env, row, column);
    NodeList *reachablePositions = nullptr;
    reachablePositions = pathplanner->getReachableNodes();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList *solution = pathplanner->getPath();

    // print the path
    printPath(env, row, column, solution);

    delete_env(env, row, column);
    delete pathplanner;
    delete reachablePositions;
    delete solution;
}

void readEnvStdin(Env &env, int &row, int &column)
{
    char c = '=';
    row = 1;
    column = 0;
    int elements = 0;
    char *chars = nullptr;
    while (std::cin.get(c) && c != (char)10)
    {
        column = column + 1;
        char *temp = new char[row * column];
        for (int i = 0; i < elements; i++)
        {
            temp[i] = chars[i];
        }
        delete[] chars;
        chars = temp;
        chars[elements++] = c;
    }

    while (std::cin.get(c))
    {
        if (c != (char)10)
        {
            if (elements < (row * column))
            {
                chars[elements++] = c;
            }
            else
            {
                char *temp = new char[++row * column];
                for (int i = 0; i < elements; i++)
                {
                    temp[i] = chars[i];
                }
                delete[] chars;
                chars = temp;
                chars[elements++] = c;
            }
        }
    }

    env = make_env(row, column);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            env[i][j] = chars[(i * column) + j];
        }
    }
    delete[] chars;
}

void printPath(Env env, int &row, int &column, NodeList *solution)
{
    for (int i = 1; i < solution->getLength() - 1; ++i)
    {
        if (solution->get(i)->getRow() == solution->get(i - 1)->getRow())
        {
            if (solution->get(i)->getCol() < solution->get(i - 1)->getCol())
            {
                env[solution->get(i)->getRow()]
                   [solution->get(i)->getCol()] = '>';
            }
            else
            {
                env[solution->get(i)->getRow()]
                   [solution->get(i)->getCol()] = '<';
            }
        }
        else
        {
            if (solution->get(i)->getRow() < solution->get(i - 1)->getRow())
            {
                env[solution->get(i)->getRow()]
                   [solution->get(i)->getCol()] = 'v';
            }
            else
            {
                env[solution->get(i)->getRow()]
                   [solution->get(i)->getCol()] = '^';
            }
        }
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            std::cout << env[i][j];
        }
        if (i != row - 1)
        {
            std::cout << std::endl;
        }
    }
}

Env make_env(const int row, const int column)
{
    Env env = nullptr;
    if (row >= 0 && column >= 0)
    {
        env = new char *[row];
        for (int i = 0; i != row; ++i)
        {
            env[i] = new char[column];
        }
    }
    return env;
}

void delete_env(Env env, int row, int column)
{
    if (row >= 0 && column >= 0)
    {
        for (int i = 0; i != row; ++i)
        {
            delete[] env[i];
        }
        delete[] env;
        env = nullptr;
    }
}