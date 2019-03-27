#include "Game.h"

using namespace std;

Game::Game(string file)
{
    this->map = new Map(file);
    this->menu();
}

void Game::loop()
{
    cin.ignore(256, '\n');
    while (this->player->makeMove())
    {
        if (this->player->checkEndGame())
            return;
    }
}

void Game::menu()
{

    int playerChoice, levelChoice = -1, algorithmChoice;

    cout << "  _____       _           _     _           _                _       _   _     " << endl;
    cout << " |  __ \\     | |         | |   | |         | |              (_)     | | | |    " << endl;
    cout << " | |__) |___ | |__   ___ | |_  | |     __ _| |__  _   _ _ __ _ _ __ | |_| |__  " << endl;
    cout << " |  _  // _ \\| '_ \\ / _ \\| __| | |    / _` | '_ \\| | | | '__| | '_ \\| __| '_ \\ " << endl;
    cout << " | | \\ \\ (_) | |_) | (_) | |_  | |___| (_| | |_) | |_| | |  | | | | | |_| | | |" << endl;
    cout << " |_|  \\_\\___/|_.__/ \\___/ \\__| |______\\__,_|_.__/ \\__, |_|  |_|_| |_|\\__|_| |_|" << endl;
    cout << "                                                   __/ |                       " << endl;
    cout << "                                                  |___/                       " << endl;
    cout << "Choose the game mode:" << endl;
    cout << "0 - Humans" << endl;
    cout << "1 - Bots" << endl;

    cin >> playerChoice;

    cout << "Choose the level (int):";

    while (!(levelChoice >= 0))
    {
        cin >> levelChoice;
    }
    if (playerChoice == 0)
    {
        player = new Human(levelChoice-1, this->map);
        return;
    }
    else if (playerChoice == 1)
    {
        cout << "Choose the algorithm:" << endl;
        cout << "0 - Depth-First Search" << endl;
        cout << "1 - Breadth-First Search" << endl;
        cout << "2 - A-Star *****" << endl;
        cin >> algorithmChoice;

        player = new AI(levelChoice-1, this->map, algorithmChoice);
    }
}