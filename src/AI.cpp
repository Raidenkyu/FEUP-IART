#include "AI.h"
#include <iostream>
#include <string>

using namespace std;

AI::AI(int level,Map *map):Player(level,map){}

bool AI::makeMove(char robot,char direction)
{
    return true;
}

/*
std::string BotPlayer::play(){

    string line;

    srand(time(NULL));   // Initialization, should only be called once.

    int robot = rand()%2;
    int move = rand()%4;

    if(robot == 0)
    line = "A";
    else line = "L";

    switch(move){
        case 0: 
        line += "u";
        break;
        case 1:
        line += "d";
        break;
        case 2:
        line += "l";
        break;
        case 3:
        line += "r";
        break;
    }
    cin.ignore();
    return line;
}*/