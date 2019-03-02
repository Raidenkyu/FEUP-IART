#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include "Player.h"
#include "Map.h"
#include "Robot.h"

class Game {
private:
    unsigned int level;
    Player * player;
    Robot Andy;
    Robot Lisa;
    std::vector<Map> maps;

public:
    Game();
    void loadMaps();
    void loop();
    void printGame();
    void run();
};

#endif