#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver()
{
    // constructor
    nodesExplored = nullptr;
}

PathSolver::~PathSolver()
{
    //deconstructor
}

void PathSolver::forwardSearch(Env env)
{
    // searches through the maze to find the goal, open list of nodes are
    //being explored, closed list has been explored and goal list just
    // contains the goal
    NodeList *closedList = new NodeList();
    NodeList *openList = new NodeList();
    NodeList *goalList = new NodeList();

    //finding the start and goal
    for (int x = 0; x != ENV_DIM; ++x)
    {
        for (int y = 0; y != ENV_DIM; ++y)
        {

            if (env[x][y] == 'S')
            {
                Node *S = new Node(x, y, 0);
                openList->addElement(S);
                closedList->addElement(S);
                std::cout << "Start Located" << x << y << std::endl;
            }

            if (env[x][y] == 'G')
            {
                Node *G = new Node(x, y, 0);
                goalList->addElement(G);
                std::cout << "Goal Located" << x << y << std::endl;
            }
        }
    }

    // initialising the search x,y, postion on the maze, d distance traveled
    // and backtrack is for when the search hits a dead end
    Node *S = openList->getNode(0);
    Node *G = goalList->getNode(0);
    int x = S->getRow();
    int y = S->getCol();
    int d = 0;
    int backtrack = 0;
    delete openList;

    for (int goalFound = 0; goalFound != 1;)
    {
        NodeList *openList = new NodeList();

        //the possible directions are added to the
        //open list
        Node *down = new Node(x + 1, y, d);
        openList->addElement(down);

        Node *Up = new Node(x - 1, y, d);
        openList->addElement(Up);

        Node *right = new Node(x, y + 1, d);
        openList->addElement(right);

        Node *left = new Node(x, y - 1, d);
        openList->addElement(left);

        //finding the smallest estimated distance
        //i initialised to a large number that couldnt show up in the maze
        //as it needs to find the smallest
        int smallest = 10000;

        for (int q = 0; q != openList->getLength(); q++)
        {
            Node *getSmall = openList->getNode(q);
            if (env[getSmall->getRow()][getSmall->getCol()] == '.')
            {
                if (smallest > getSmall->getEstimatedDist2Goal(G))
                {
                    smallest = getSmall->getEstimatedDist2Goal(G);
                }
            }
        }
        //I used foundpath so the pathfinder only goes in one direction per loop and doesnt
        //split
        int foundPath = 0;

        for (int q = 0; q != openList->getLength(); q++)
        {

            Node *getPath = openList->getNode(q);

            //checking if the node is the goal
            if (env[getPath->getRow()][getPath->getCol()] == 'G')
            {

                ++goalFound;
                ++foundPath;
            }
            //checking if the node has been explored or can be explored
            if (env[getPath->getRow()][getPath->getCol()] == '.')
            {
                ++foundPath;
                if (smallest == getPath->getEstimatedDist2Goal(G))
                {
                    //adding distance and setting the new location of x and y
                    ++d;
                    x = getPath->getRow();
                    y = getPath->getCol();
                    // marking on the map the direction taken
                    env[x][y] = 'X';

                    Node *q = new Node(x, y, d);
                    closedList->addElement(q);
                    //if a path was found backtracking is set to 0
                    backtrack = 0;
                }
            }
        }
        //if a path could not be found the xy postion reverts to the previous spot
        if (foundPath == 0)
        {
            ++backtrack;
            env[x][y] = 'X';
            Node *back = closedList->getNode(closedList->getLength() - backtrack);
            x = back->getRow();
            y = back->getCol();
        }

        delete openList;
    }

    *openList = *closedList;

    //deep copy of the closed list
    nodesExplored = new NodeList(*closedList);
}

NodeList *PathSolver::getNodesExplored()
{

    return nodesExplored;
}

NodeList *PathSolver::getPath(Env env)
{

    int x = 0;
    int y = 0;
    //cleaning the maze of the markings made during the pathfinding
    for (int mx = 0; mx != ENV_DIM; ++mx)
    {
        for (int my = 0; my != ENV_DIM; ++my)
        {

            if (env[mx][my] != 'S' && env[mx][my] != 'G' && env[mx][my] != '=')
            {
                env[mx][my] = '.';
            }
            if (env[mx][my] == 'G')
            {
                x = mx;
                y = my;
            }
        }
    }
    //initialising values
    //px is the location of the node on the maze

    int pX = 0;
    int pY = 0;

    NodeList *solution = new NodeList();
    for (int goalFound = 0; goalFound != 1;)

    {
        NodeList *bestPath = new NodeList();
        //find any node that is available to travel to
        for (int i = 0; i != nodesExplored->getLength(); i++)
        {

            //gx is checking if the node is the goal
            //cX is checking of the node is next to the current node
            Node *current = nodesExplored->getNode(i);
            int cX = current->getRow();
            int cY = current->getCol();

            if (cX == x + 1 && cY == y)
            {
                Node *down = new Node(x + 1, y, current->getDistanceTraveled());
                bestPath->addElement(down);
            }
            if (cX == x - 1 && cY == y)
            {
                Node *up = new Node(x - 1, y, current->getDistanceTraveled());
                bestPath->addElement(up);
            }
            if (cX == x && cY == y + 1)
            {
                Node *right = new Node(x, y + 1, current->getDistanceTraveled());
                bestPath->addElement(right);
            }
            if (cX == x && cY == y - 1)
            {
                Node *left = new Node(x, y - 1, current->getDistanceTraveled());
                bestPath->addElement(left);
            }
        }
        //find the node with the most distance traveled
        // if the nodes are both accessable and one has a higher
        //distance traveled we can assume that the path had
        //to backtrack therefore that is the correct path

        int highest = 1000000;
        int solutionI = 0;
        for (int i = 0; i != bestPath->getLength(); i++)
        {

            if (highest >= bestPath->getNode(i)->getDistanceTraveled())
            {
                highest = bestPath->getNode(i)->getDistanceTraveled();
                Node *path = bestPath->getNode(i);
                pX = path->getRow();
                pY = path->getCol();
                solutionI = i;
            }
        }
        //adding the correct path to the env to print
        Node *solutionNode = bestPath->getNode(solutionI);
        solution->addElement(solutionNode);

        //find the position in relation to the current node make sure it 
        //doesn't overwrite the S or G

        if (env[pX][pY] == 'S')
        {
            ++goalFound;
        }

        if (pX == x + 1 && pY == y)
        {
            x = pX;
            y = pY;
            if (env[x][y] != 'G' && env[x][y] != 'S')
            {
                env[x][y] = '^';
            }
        }
        if (pX == x - 1 && pY == y)
        {
            x = pX;
            y = pY;
            if (env[x][y] != 'G' && env[x][y] != 'S')
            {
                env[x][y] = 'v';
            }
        }
        if (pX == x && pY == y + 1)
        {
            x = pX;
            y = pY;
            if (env[x][y] != 'G' && env[x][y] != 'S')
            {
                env[x][y] = '<';
            }
        }
        if (pX == x && pY == y - 1)
        {
            x = pX;
            y = pY;
            if (env[x][y] != 'G' && env[x][y] != 'S')
            {
                env[x][y] = '>';
            }
        }
    }

    return solution;
}
