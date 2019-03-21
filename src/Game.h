#ifndef GAME_H_
#define GAME_H_

#include "Player.h"
#include "AI.h"
#include "Human.h"
#include "Map.h"
#include "Robot.h"
#include "macros.h"

class Game {
private:
    u_int level;
    Player * player;
    Map * map;
    
public:
    Game(int HumanOrBot,int level,std::string file);

    void loop();
};

#endif