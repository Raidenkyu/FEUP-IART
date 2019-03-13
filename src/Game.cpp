#include "Game.h"
#include <fstream>
#include <iostream>
#include <climits>

using namespace std;

Game::Game(int HumanOrBot) : level(0), Andy('A'), Lisa('L')
{
    if(HumanOrBot == 0)
     player = new Player();
    
    else if (HumanOrBot == 1)
     player = new BotPlayer();
    this->loadMaps();
}

void Game::loadMaps()
{
    ifstream maps_file("res/maps.txt");
    string line;
    vector<vector<char>> matrix;
    if (maps_file.is_open())
    {
        int sizeX,sizeY;
        maps_file >> sizeX >> sizeY;
        getline(maps_file, line);
        for(int i=0;i<sizeX;i++)
        {
            vector<char> temp;
            matrix.push_back(temp);
        }     
        for(int i=0;i<sizeY;i++)
        {
            getline(maps_file, line);
            for(int j=0;j<sizeX;j++)
            {
                matrix[j].push_back(line[j]);
            }
        }
        Map map(0,matrix);
        this->maps.push_back(map);
    }
    else
    {
        cout << "Unable to locate maps file" << endl;
        exit(1);
    }
}

void Game::run()
{
    this->maps[this->level].setRobots(this->Andy, this->Lisa);
    this->printGame();
    this->loop();
}

void Game::loop()
{
    string play;
    bool checkTarget = true;
    do
    {
        play = this->player->play();
        this->moveRobots(play);
        this->printGame();
        checkTarget = !(this->maps[this->level].checkTarget(this->Andy, this->Lisa));
    } while (play != "q" && checkTarget);
}

void Game::printGame()
{
    vector<vector<char>> map = this->maps[this->level].getMap();
    map[this->Andy.getX()][this->Andy.getY()] = 'A';
    if (this->Lisa.getX() != -1)
    {
        map[this->Lisa.getY()][this->Lisa.getX()] = 'L';
    }
    for (unsigned int i = 0; i < map[0].size(); i++)
    {
        for (unsigned int j = 0; j < map.size(); j++)
        {
            cout << map[j][i];
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
        return this->Andy.moveDFS(this->maps[this->level].getMap());
        break;
    case 'L':
        return this->Lisa.moveDFS(this->maps[this->level].getMap());
        break;
    default:
        return false;
    };
}