#ifndef AI_H_
#define AI_H_

#include <string>
#include "Player.h"
#include "Map.h"
#include "macros.h"
#include "Node.h"
#include <set>

class AI: public Player {
private:

    //função dfs recursiva
    bool dfs(int custo,std::vector<std::vector<char>> map_char,std::vector<std::pair<u_int,u_int>> robot_positions,std::vector<std::vector<std::pair<u_int,u_int>>> &visited,std::vector<std::pair<u_int,char>> moves);

    //funcao bfs
    bool bfs();

    //pega no node final e mete os paizinhos dele todos no best move (incluindo ele), em ordem inversa
    void TranslateToBestMove(Node * node);
    //testa se um posição já foi passada
    bool alreadyBeenOn(std::vector<std::vector<std::pair<u_int,u_int>>> visited,u_int i, std::pair<u_int,u_int> position,std::vector<std::pair<u_int,u_int>> robot_position);

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
    u_int limite;
    bool evitar_ciclos = true;

    long expancoes;

    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;

public:
    AI(){}
    AI(int level,Map * map, int algorithm);

    //faz movimento de AI
    bool makeMove();


    //faz a procura em profundidade
    bool dfs();


    //A-star Search
    bool astar();

    std::pair<u_int, u_int> getNewCoords(int robotIndex, int direction, std::vector<std::pair<u_int, u_int>> robotsCoords);
    Node * findNodeOnList(std::set<Node*> & nodes, std::vector<std::pair<u_int,u_int>> robotsCoords);
    void releaseNodes(std::set<Node*> & nodes);
    bool detectCollision(std::pair<u_int,u_int> oldCoords, std::pair<u_int,u_int> newCoords);
    char numToPlay(int num);

    void setIndexSol(u_int index){this->index_sol=index;}
};

#endif