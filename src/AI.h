#ifndef AI_H_
#define AI_H_

#include <string>
#include "Player.h"
#include "Map.h"
#include "macros.h"

class AI: public Player {
private:

    //função dfs recursiva
    bool dfs(int custo,std::vector<std::vector<char>> map_char,std::vector<std::pair<u_int,u_int>> robot_positions,std::vector<std::vector<std::pair<u_int,u_int>>> visited,std::vector<std::pair<u_int,char>> moves);

    //testa se um posição já foi passada
    bool alreadyBeenOn(std::vector<std::pair<u_int,u_int>> visited,std::pair<u_int,u_int> position);

    //melhor movimento
    std::vector<std::pair<u_int,char>> best_move;
    //melhor custo
    int best_custo;

    //algoritmo a usar
    int algorithm;

    //Chooses one of the existing algorithms and computes a solution
    bool computeSolution();

    //Saber se o algoritmo já foi calculado
    bool alg_calculated;
    u_int index_sol;

public:
    AI(){}
    AI(int level,Map * map, int algorithm);

    //faz movimento de AI
    bool makeMove();

    //faz a procura em profundidade
    bool dfs();
};

#endif