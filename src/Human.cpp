#include "Human.h"

using namespace std;

Human::Human(int level,Map *map):Player(level,map){}

bool Human::makeMove(char robot,char direction)
{
    int robot_number= this->transformCharToNumber(robot);
    switch(direction)
    {
    case 't':
    case 'T':
    case 'u':
    case 'U':
        return this->PlayTop(robot_number);
        break;
    case 'b':
    case 'B':
    case 'd':
    case 'D':
        return this->PlayBottom(robot_number);
        break;
    case 'r':
    case 'R':
        return this->PlayRight(robot_number);
        break;
    case 'l':
    case 'L':
        return this->PlayLeft(robot_number);
        break;
    }
    return false;
}