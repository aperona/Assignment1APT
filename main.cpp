//Aiden Perona s3539619
/*
for this assignment i have completed milestone 1,2,3
for milestone 1 i created 4 tests that i believed you stretch the 
abilities of the program. for milestone 2 i read the maze env with std::in
and go through the maze using two lists open and closed, open being the 
points reachable from the current and closed being points already searched
when searching the map i marked the env with X to sygnify that the point had been searched
i dont know if this was the correct way of determining that the node was in 
the list but it made sense to me.
Once the goal has been found a deep copy is produced for the getpath

milestone 3 uses the deep copy to find the best path through comparing
distance traveled of the available nodes, when the correct node is
found the spot on the env is marked with the direction


*/




#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList *solution);

int main(int argc, char **argv)
{

  // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
  // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
  // AS YOU GO ALONG.
  // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
  //    std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
  //    testNode();
  //    testNodeList();
  //  std::cout << "DONE TESTING" << std::endl << std::endl;

  // Load Environment
  Env env;
  readEnvStdin(env);

  // Solve using forwardSearch
  // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
  PathSolver *pathSolver = new PathSolver();
  pathSolver->forwardSearch(env);

  NodeList *exploredPositions = nullptr;
  exploredPositions = pathSolver->getNodesExplored();

  // Get the path
  // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
  NodeList *solution = pathSolver->getPath(env);

  printEnvStdout(env, solution);

  delete pathSolver;
  delete exploredPositions;
  delete solution;
}

void readEnvStdin(Env env)
{
  //reading in a value for each point in the maze left to right top to bottom
  std::cout << "Enter maze values:" << std::endl;
  for (int x = 0; x != ENV_DIM; ++x)
  {
    for (int y = 0; y != ENV_DIM; ++y)
    {

      std::cin >> env[x][y];
    }
  }
}

void printEnvStdout(Env env, NodeList *solution)
{
  //printing the size of the path and the nodes contained
  std::cout << "Solution size: " << solution->getLength() << std::endl;
  for (int x = 0; x != solution->getLength(); ++x)
  {
    Node *getAll = solution->getNode(x);

    std::cout << "Node " << x << ": " << getAll->getRow() << ",";
    std::cout << getAll->getCol() << ",";
    std::cout << getAll->getDistanceTraveled() << std::endl;
  }

  //printing a value for each point in the maze left to right top to bottom
  for (int x = 0; x != ENV_DIM; ++x)
  {
    for (int y = 0; y != ENV_DIM; ++y)
    {
      std::cout << env[x][y];
    }
    std::cout << std::endl;
  }
}

void testNode()
{
  std::cout << "TESTING Node" << std::endl;

  // Make a Node and print out the contents
  Node *node = new Node(1, 1, 2);
  std::cout << node->getRow() << ",";
  std::cout << node->getCol() << ",";
  std::cout << node->getDistanceTraveled() << std::endl;
  delete node;

  // Change Node and print again
  node = new Node(4, 2, 3);
  std::cout << node->getRow() << ",";
  std::cout << node->getCol() << ",";
  std::cout << node->getDistanceTraveled() << std::endl;
  delete node;
}

void testNodeList()
{
  std::cout << "TESTING NodeList" << std::endl;

  // Make a simple NodeList, should be empty size
  NodeList *nodeList = new NodeList();
  std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

  // Add a Node to the NodeList, print size
  Node *b1 = new Node(1, 1, 1);
  nodeList->addElement(b1);
  std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

  // Add second Nodetest
  Node *b2 = new Node(0, 0, 1);
  nodeList->addElement(b2);
  std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

  // Test Get-ith - should be 0,0,1
  Node *getB = nodeList->getNode(1);
  std::cout << getB->getRow() << ",";
  std::cout << getB->getCol() << ",";
  std::cout << getB->getDistanceTraveled() << std::endl;

  // Print out the NodeList
  std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;

  for (int x = 0; x != nodeList->getLength(); ++x)
  {
    Node *getAll = nodeList->getNode(x);
    std::cout << "Node " << x << ": " << getAll->getRow() << ",";
    std::cout << getAll->getCol() << ",";
    std::cout << getAll->getDistanceTraveled() << std::endl;
  }
}