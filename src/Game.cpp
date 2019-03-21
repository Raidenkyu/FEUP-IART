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
    while(this->player->makePlay()){}
}


    
/*



void Game::printGame()
{
    vector<vector<char>> map = this->maps[this->level].getMap();
    map[this->Andy.getY()][this->Andy.getX()] = 'A';
    map[this->Lisa.getY()][this->Lisa.getX()] = 'L';
    for (unsigned int i = 0; i < map.size(); i++)
    {
        for (unsigned int j = 0; j < map[i].size(); j++)
        {
            cout << map[i][j];
        }
        cout << endl;
    }
}

bool Game::moveRobots(string play)
{
    char robot = toupper(play[0]);
    char direction = toupper(play[1]);
    
    switch (robot)
    {
    case 'A':
        return this->Andy.move(direction,this->maps[this->level].getMap());
        break;
    case 'L':
        return this->Lisa.move(direction,this->maps[this->level].getMap());
        break;
    default:
        return false;
    };
}*/