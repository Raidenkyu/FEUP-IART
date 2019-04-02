#ifndef NODE_H_
#define NODE_H_

#include "macros.h"

class Node
{
public:
  u_int G, H;
  std::vector<std::pair<u_int, u_int>> robotsCoords;
  std::vector<std::pair<u_int, char>> moves;
  std::vector<std::vector<char>> map_char;
  Node(std::vector<std::pair<u_int, u_int>> robotsCoords, std::vector<std::vector<char>> map_char);
  Node(std::vector<std::pair<u_int, u_int>> robotsCoords, std::vector<std::vector<char>> map_char, std::vector<std::pair<u_int, char>> moves);

   u_int getScore() const;

  bool operator<(const Node &n) const
  {
    if (this->robotsCoords < n.robotsCoords)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  struct NodeComp
{
  bool operator()(const Node* lhs, const Node* rhs) const  {
      return (lhs->robotsCoords < rhs->robotsCoords);
      }
};
};



#endif