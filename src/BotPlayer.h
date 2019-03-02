#ifndef BOT_PLAYER_H_
#define BOT_PLAYER_H_

#include <string>

class BotPlayer: public Player {
public:
    BotPlayer();
    std::string play();
};

#endif