#include "Game.h"
#include <iostream>

using namespace std;


int menu(){

   
 int choice;

cout << "  _____       _           _     _           _                _       _   _     " << endl;
cout << " |  __ \\     | |         | |   | |         | |              (_)     | | | |    " << endl;
cout << " | |__) |___ | |__   ___ | |_  | |     __ _| |__  _   _ _ __ _ _ __ | |_| |__  " << endl;
cout << " |  _  // _ \\| '_ \\ / _ \\| __| | |    / _` | '_ \\| | | | '__| | '_ \\| __| '_ \\ " << endl;
cout << " | | \\ \\ (_) | |_) | (_) | |_  | |___| (_| | |_) | |_| | |  | | | | | |_| | | |" << endl;
cout << " |_|  \\_\\___/|_.__/ \\___/ \\__| |______\\__,_|_.__/ \\__, |_|  |_|_| |_|\\__|_| |_|" << endl;
cout << "                                                   __/ |                       " << endl;
cout << "                                                  |___/                       "  << endl;
    cout << "Choose the game mode:" << endl;
    cout << "0 - Humans" << endl;
    cout << "1 - Bots" << endl;
   
            cin >> choice;
        
        
    return choice;
}
int main()
{
    int HumanOrBot = menu();
    Game *  LabyrinthRobots = new Game(HumanOrBot);
    LabyrinthRobots->run();
    return 0;
}
