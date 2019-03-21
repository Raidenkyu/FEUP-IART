#ifndef PLAYER_H_
#define PLAYER_H_

#include "macros.h"
#include "Map.h"

class Player {

protected:

    int level;
    u_int number_robots;
    std::vector<std::pair<u_int,u_int>> robot_positions;
    std::vector<std::vector<char>> map_char;

    Map * map;

    void printMap();

    int transformCharToNumber(char ch);
    char transformNumberToChar(int number);


public:
    //Constructor
    Player(int level,Map * map);

    //Diz qual a posição que vai ter mas não move
    std::pair<u_int,u_int> MoveTop(int robot_number);
    std::pair<u_int,u_int> MoveBottom(int robot_number);
    std::pair<u_int,u_int> MoveRight(int robot_number);
    std::pair<u_int,u_int> MoveLeft(int robot_number);

    //Faz um movimento
    bool PlayTop(int robot_number);
    bool PlayBottom(int robot_number);
    bool PlayRight(int robot_number);
    bool PlayLeft(int robot_number);

    //Intermedio antes de chamar makeMove
    bool makePlay();
    //Função que é chamada a cada movimento feito. Implementado pela funções abstratas
    virtual bool makeMove(char robot,char direction) = 0;

    //Substitui a posição no map_char do robot. Substitui a posição no vector de posições do robot
    void replacePosition(int robot_number,std::pair<u_int,u_int> current,std::pair<u_int,u_int> to);
};

#endif