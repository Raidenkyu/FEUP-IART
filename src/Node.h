#ifndef NODE_H_
#define NODE_H_

#include "macros.h"

class Node
{
  public:
    uint G, H;
    std::vector<std::pair<u_int,u_int>> robotsCoords;
    Node *parent;
    std::pair<u_int,char> move;

    Node(std::vector<std::pair<u_int,u_int>> robotsCoords, Node *parent_ = nullptr);
    u_int getScore();
    u_int computeHeuristic(std::vector<std::pair<u_int,u_int>> targets);
};

#endif