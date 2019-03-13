#ifndef ROBOT_H_
#define ROBOT_H_


#include <vector>

class Robot {
private: 
    char type;
    int x,y;

    std::pair<int,int> MoveTop(std::vector<std::vector<char>> map,std::pair<int,int> currentPos);
    std::pair<int,int> MoveBottom(std::vector<std::vector<char>> map,std::pair<int,int> currentPos);
    std::pair<int,int> MoveRight(std::vector<std::vector<char>> map,std::pair<int,int> currentPos);
    std::pair<int,int> MoveLeft(std::vector<std::vector<char>> map,std::pair<int,int> currentPos);

public:
    Robot(char type);
    bool move(char direction, std::vector<std::vector<char>> map);
    void setPosition(int x, int y);
    int getX();
    int getY();
    char getType();
};

#endif