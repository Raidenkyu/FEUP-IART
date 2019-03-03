#include "Game.h"
#include <fstream>
#include <iostream>

using namespace std;

Game::Game() : level(0), player(new Player()), Andy('A'), Lisa('L')
{
    this->loadMaps();
}

void Game::loadMaps()
{
    ifstream maps_file("res/maps.txt");
    string line;
    vector<vector<char>> matrix;
    vector<char> aux;
    int num = 0;
    if (maps_file.is_open())
    {
        while (getline(maps_file, line))
        {
            if (line == "END")
            {
                num++;
                Map map(num, matrix);
                this->maps.push_back(map);
                matrix.clear();
                continue;
            }
            for (unsigned int i = 0; i < line.length(); i++)
            {
                aux.push_back(line[i]);
            }
            matrix.push_back(aux);
            aux.clear();
            line.clear();
        }
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
    map[this->Andy.getY()][this->Andy.getX()] = 'A';
    if (this->Lisa.getX() != -1)
    {
        map[this->Lisa.getY()][this->Lisa.getX()] = 'L';
    }
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
}