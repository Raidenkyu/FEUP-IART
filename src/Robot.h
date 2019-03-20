#ifndef ROBOT_H_
#define ROBOT_H_

#include <iostream>
#include <vector>
#include <utility>
#include <climits>

typedef unsigned int u_int;

class Robot {
private: 
    char type;
    int x,y;
    int minCusto;
    std::vector<std::pair<int,int>> minVisited;
    std::pair<int,int> target;

    std::pair<int,int> MoveTop(std::vector<std::vector<char>> map,std::pair<int,int> currentPos);
    std::pair<int,int> MoveBottom(std::vector<std::vector<char>> map,std::pair<int,int> currentPos);
    std::pair<int,int> MoveRight(std::vector<std::vector<char>> map,std::pair<int,int> currentPos);
    std::pair<int,int> MoveLeft(std::vector<std::vector<char>> map,std::pair<int,int> currentPos);
    void dfs(std::vector<std::vector<char>> map,std::pair<int,int> currentPos,int custo,std::vector<std::pair<int,int>> visited,std::vector<std::pair<int,int>> movesUntilNow);
    
    bool alreadyBeenOn(std::vector<std::pair<int,int>> visited,std::pair<int,int> pos);

public:
    Robot(char type);
    bool move(char direction, std::vector<std::vector<char>> map);
    bool moveDFS(std::vector<std::vector<char>> map);
    void setPosition(int x, int y);
    int getX();
    int getY();
    char getType();
};

#endif