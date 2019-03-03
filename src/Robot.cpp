#include "Robot.h"

using namespace std;

Robot::Robot(char type) : type(type), x(-1), y(-1) {}

bool Robot::move(char direction, vector<vector<char>> map)
{
    int xVector = 0;
    int yVector = 0;

    switch (direction)
    {
    case 'L':
        xVector = -1;
        break;
    case 'R':
        xVector = 1;
        break;
    case 'U':
        yVector = -1;
        break;
    case 'D':
        yVector = 1;
        break;

    default:
        return false;
    }

    while(map[this->getY()+yVector][this->getX()+xVector] == ' '){
        this->x += xVector;
        this->y += yVector;
    }
    return true;

}

void Robot::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Robot::getX()
{
    return this->x;
}

int Robot::getY()
{
    return this->y;
}