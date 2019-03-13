#include "Robot.h"
#include <stdio.h>
#include <ctype.h>

using namespace std;

Robot::Robot(char type) : type(type), x(-1), y(-1) {}




std::pair<int,int> Robot::MoveTop(vector<vector<char>> map, std::pair<int,int> currentPos)
{
    int currentX=currentPos.first;
    int currentY=currentPos.second;
    while(currentX>0 && currentX<=map.size() && currentY>0 && currentY<=map[0].size())
    {
        if(map[currentX][currentY]!= ' ')
        {
            return make_pair(currentX,currentY);
        }
        else
        {
            currentX--;
        }
    }
    return make_pair(currentX,currentY);
}
std::pair<int,int> Robot::MoveBottom(vector<vector<char>> map,std::pair<int,int> currentPos)
{
    int currentX=currentPos.first;
    int currentY=currentPos.second;
    while(currentX>0 && currentX<=map.size() && currentY>0 && currentY<=map[0].size())
    {
        if(map[currentX][currentY]!= ' ')
        {
            return make_pair(currentX,currentY);
        }
        else
        {
            currentX++;
        }
    }
    return make_pair(currentX,currentY);
}
std::pair<int,int> Robot::MoveLeft(vector<vector<char>> map,std::pair<int,int> currentPos)
{
    int currentX=currentPos.first;
    int currentY=currentPos.second;
    while(currentX>0 && currentX<=map.size() && currentY>0 && currentY<=map[0].size())
    {
        if(map[currentX][currentY]!= ' ')
        {
            return make_pair(currentX,currentY);
        }
        else
        {
            currentY--;
        }
    }
    return make_pair(currentX,currentY);
}
std::pair<int,int> Robot::MoveRight(vector<vector<char>> map,std::pair<int,int> currentPos)
{
    int currentX=currentPos.first;
    int currentY=currentPos.second;
    while(currentX>0 && currentX<=map.size() && currentY>0 && currentY<=map[0].size())
    {
        if(map[currentX][currentY]!= ' ')
        {
            return make_pair(currentX,currentY);
        }
        else
        {
            currentY++;
        }
    }
    return make_pair(currentX,currentY);
}


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

    while (map[this->getY() + yVector][this->getX() + xVector] == ' ')
    {

        this->x += xVector;
        this->y += yVector;
    }

    if (toupper(map[this->getY() + yVector][this->getX() + xVector]) == this->getType())
    {

        this->x += xVector;
        this->y += yVector;
        map[this->getY() + yVector][this->getX() + xVector] = this->getType();
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

char Robot::getType()
{
    return this->type;
}