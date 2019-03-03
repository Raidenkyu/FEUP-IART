#ifndef ROBOT_H_
#define ROBOT_H_


#include <vector>

class Robot {
private: 
    char type;
    int x,y;
public:
    Robot(char type);
    bool move(char direction, std::vector<std::vector<char>> map);
    void setPosition(int x, int y);
    int getX();
    int getY();
};

#endif