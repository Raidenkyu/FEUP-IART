#include "Game.h"

using namespace std;

Game::Game(string file)
{
    this->map = new Map(file);
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
    string ler;
    while (true)
    {
        clearScreen();

        int playerChoice, levelChoice = -1, algorithmChoice;

        cout << "  _____       _           _     _           _                _       _   _     " << endl;
        cout << " |  __ \\     | |         | |   | |         | |              (_)     | | | |    " << endl;
        cout << " | |__) |___ | |__   ___ | |_  | |     __ _| |__  _   _ _ __ _ _ __ | |_| |__  " << endl;
        cout << " |  _  // _ \\| '_ \\ / _ \\| __| | |    / _` | '_ \\| | | | '__| | '_ \\| __| '_ \\ " << endl;
        cout << " | | \\ \\ (_) | |_) | (_) | |_  | |___| (_| | |_) | |_| | |  | | | | | |_| | | |" << endl;
        cout << " |_|  \\_\\___/|_.__/ \\___/ \\__| |______\\__,_|_.__/ \\__, |_|  |_|_| |_|\\__|_| |_|" << endl;
        cout << "                                                   __/ |                       " << endl;
        cout << "                                                  |___/                       " << endl;
        do
        {
        cout << "Choose the game mode:" << endl;
        cout << "0 - Exit" << endl;
        cout << "1 - Humans" << endl;
        cout << "2 - Bots" << endl;
            cin >> ler;
        } while (!is_number(ler));
        playerChoice = stoi(ler);

        if (playerChoice == 0)
            return;
        else if (playerChoice == 1)
        {
            player = new Human(this->levelChoose() - 1, this->map);
            this->loop();

            cout << "Press ENTER to continue" << endl;

            cin.get();
        }
        else if (playerChoice == 2)
        {
            levelChoice = this->levelChoose();

            do
            {
            cout << "Choose the algorithm:" << endl;
            cout << "0 - Depth-First Search" << endl;
            cout << "1 - Breadth-First Search" << endl;
            cout << "2 - A-Star *****" << endl;
            cout << "3 - Iterative Deepening Depth-First Search" << endl;
            cout << "4 - Greedy Algorithm" << endl;
            cout << "5 - Second A*" << endl;
                cin >> ler;
            } while (!is_number(ler));
            algorithmChoice = stoi(ler);

            player = new AI(levelChoice - 1, this->map, algorithmChoice);
            this->loop();

            cout << "Press ENTER to continue" << endl;

            cin.get();
        }
        else
        {
            continue;
        }
    }
}

int Game::levelChoose()
{
    int levelChoice = 0;
    string ler;
    while (!(levelChoice > 0 && levelChoice <= (int)this->map->getMapNumber()))
    {
        do
        {
            cout << "Choose the level (int):";
            cin >> ler;
        } while (!is_number(ler));
        levelChoice = stoi(ler);
    }
    return levelChoice;
}