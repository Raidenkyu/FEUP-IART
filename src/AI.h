#ifndef AI_H_
#define AI_H_

#include <string>
#include "Player.h"
#include "Map.h"

class AI: public Player {
public:
    AI(){}
    AI(int level,Map * map);

    bool makeMove(char robot,char direction);
};

#endif