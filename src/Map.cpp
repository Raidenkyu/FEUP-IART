#include "Map.h"

using namespace std;

Map::Map(int num, vector<vector<char>> & charMap): 
    num(num),
    charMap(charMap),
    AndyX(-1),
    AndyY(-1),
    LisaX(-1),
    LisaY(-1),
    targetAX(-1),
    targetAY(-1),
    targetLX(-1),
    targetLY(-1) {
    for(unsigned int i = 0; i< this->charMap.size();i++){
        for(unsigned int j = 0; j < this->charMap[i].size();j++){
            if(this->charMap[i][j] == 'A'){
                this->AndyY = i;
                this->AndyX = j;
            }
            else if(this->charMap[i][j] == 'L'){
                this->LisaY = i;
                this->LisaX = j;
            }
            else if(this->charMap[i][j] == 'a'){
                this->targetAY = i;
                this->targetAX = j;
            }
            else if(this->charMap[i][j] == 'l'){
                this->targetLY = i;
                this->targetLX = j;
            }
        }
    }
}

vector<vector<char>> Map::getMap(){
    return this->charMap;
}

void Map::setRobots(Robot & Andy, Robot & Lisa){
    Andy.setPosition(this->AndyX,this->AndyY);
    Lisa.setPosition(this->LisaX,this->LisaY);
}

bool Map::checkTarget(Robot & Andy, Robot & Lisa){
    if(this->targetLX == -1){
        return ((Andy.getX() == this->targetAX)  &&(Andy.getY() == this->targetAY));
    }
    else{
        bool checkAndy = (Andy.getX() == this->targetAX)  && (Andy.getY() == this->targetAY);
        bool checkLisa = (Lisa.getX() == this->targetLX)  && (Lisa.getY() == this->targetLY);
        return (checkAndy && checkLisa);
    }
}