#include "Game.h"

using namespace std;

Game::Game(int HumanOrBot,int level,string file)
{
    this->map=new Map(file);
    if(HumanOrBot == 0)
        player = new Human(level,this->map);
    
    else if (HumanOrBot == 1)
        player = new AI(level,this->map);
}


void Game::loop()
{
    while(this->player->makePlay())
    {
        if(this->player->checkEndGame())
            return ;
    }
}