#include "Node.h"
#include <iostream>

Node::Node(int row, int col, int dist_traveled) : row(row), col(col), dist_traveled(dist_traveled)
{
  
    // this->row=row;
    // this->col=col;
    // this->dist_traveled=dist_traveled;
}

Node::~Node()
{
   
    // delete row;
    // delete col;
    // delete dist_traveled;
}

int Node::getRow()
{
    return row;
}

int Node::getCol()
{
    return col;
}

int Node::getDistanceTraveled()
{
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
 
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node *goal)
{
    //calculating the estimated distance to goal

    //calculating the manhattan distance by subtracting the active nodes col and goals col and adding it with the
    //subtracted rows
    int manhattan = (col - goal->getCol()) + (row - goal->getRow());

    //estimating the distance to goal by subtracing the dist traveled from the manhattan distance
    int Dist2Goal = dist_traveled - manhattan;

    return Dist2Goal;
}
