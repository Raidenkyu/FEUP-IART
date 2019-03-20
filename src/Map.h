#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include "Robot.h"

class Map {
private:
    int num;
    std::vector<std::vector<char>> charMap;
    int AndyX,AndyY;
    int LisaX,LisaY;
    int targetAX,targetAY;
    int targetLX,targetLY;
public:
    Map(int level, std::vector<std::vector<char>> & charMap);
    std::vector<std::vector<char>> getMap();
    void setRobots(Robot & Andy, Robot & Lisa);
    bool checkTarget(Robot & Andy, Robot & Lisa);
};

#endif