#ifndef NODE_H_
#define NODE_H_

#include "macros.h"

class Node
{
  public:
    u_int G, H;
    std::vector<std::pair<u_int,u_int>> robotsCoords;
    Node *parent;
    std::pair<u_int,char> move;
    std::vector<std::vector<char>> map_char;
    Node(std::vector<std::pair<u_int,u_int>> robotsCoords, std::vector<std::vector<char>> map_char, Node *parent_ = nullptr);
  
    u_int getScore();
    u_int computeHeuristic(std::vector<std::pair<u_int,u_int>> targets);
};

#endif