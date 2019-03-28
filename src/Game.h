#ifndef GAME_H_
#define GAME_H_

#include "Player.h"
#include "AI.h"
#include "Human.h"
#include "Map.h"
#include "macros.h"

class Game {
private:
    u_int level;
    Player * player;
    Map * map;
    int levelChoose();
    
public:
    Game(std::string file);
    void menu();
    void loop();
};

#endif