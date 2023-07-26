# Path Planning in a 2D Environment for a Simple Robot

This repository contains a C++ program that enables a simple robot to plan a path in a 2D environment, represented as an ASCII grid, with obstacles and goals defined.

## Overview

The robot operates in a 2D grid-based environment represented by ASCII characters:

- `=` denotes a wall or obstacle. The robot cannot pass through these.
- `.` signifies an open space where the robot can move.
- `S` marks the starting position of the robot.
- `G` is the goal that the robot is trying to reach.

The program executes two main tasks:

1. **Identify Reachable Positions**: It finds all possible locations that the robot can reach from the starting position, counting the steps needed to reach each position.
2. **Path Planning**: Using the identified reachable positions, it finds a path from the robot’s starting position to the specified goal coordinate.

The robot can only move in four directions (left, right, up, or down) from its current cell, but not diagonally. The direction the robot is "facing" is not considered in this implementation.

## Implementation

The program executes the following steps:

1. Reads a 20x20 environment from standard-input (`std::cin`).
2. Finds the robot’s starting position within the environment (denoted by “S”).
3. Executes the Identify Reachable Positions algorithm.
4. Executes the Path Planning algorithm to find a path.
5. Prints out the environment and the path to be followed by the robot to standard output (`std::cout`).

