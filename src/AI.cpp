#include "AI.h"
#include <algorithm>
#include <queue>

using namespace std;

AI::AI(int level, Map *map, int algorithm) : Player(level, map),
                                             algorithm(algorithm)
{
    this->alg_calculated = this->computeSolution();
    this->index_sol = 0;
}

bool AI::makeMove()
{

    if (this->alg_calculated)
    {

        this->map->printMap(this->level, this->robot_positions);
        cout << "Press ENTER to get next step" << endl;

        cin.get();
        if (this->index_sol >= this->best_move.size())
        {
            this->map->printMap(this->level, this->robot_positions);
            this->alg_calculated = false;
            return false;
        }
        u_int robot_number = this->best_move[this->index_sol].first;
        char direction = this->best_move[this->index_sol].second;
        switch (direction)
        {
        case 't':
        case 'T':
        case 'u':
        case 'U':
            this->PlayTop(robot_number);
            break;
        case 'b':
        case 'B':
        case 'd':
        case 'D':
            this->PlayBottom(robot_number);
            break;
        case 'r':
        case 'R':
            this->PlayRight(robot_number);
            break;
        case 'l':
        case 'L':
            this->PlayLeft(robot_number);
            break;
        }

        this->index_sol++;
        if (this->index_sol >= this->best_move.size())
        {
            this->map->printMap(this->level, this->robot_positions);
            this->alg_calculated = false;
            return false;
        }
    }
    else
    {
        cout << "Solution not found! " << endl;
        return false;
    }
    return true;
}

bool AI::computeSolution()
{
    this->expancoes = 0;
    bool solutionFound = false;
    this->map->printMap(this->level, this->robot_positions);
    cout << "Computing a Solution. Wait a few seconds" << endl;
    this->start = chrono::high_resolution_clock::now();
    switch (this->algorithm)
    {
    case DFS:
        solutionFound = this->dfs();
        break;
    case BFS:
        solutionFound = this->bfs();
        break;
    case ASTAR:
        solutionFound = this->astar();
        break;
    case IDFS:
        solutionFound = this->iterativeDfs();
        break;
    case GREEDY:
        solutionFound = this->greedy();
        break;
    case ASTARSECOND:
        solutionFound = this->astartSecond();
        break;
    default:
        cout << "Invalid Algorithm" << endl;
        exit(0);
    }
    this->end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = this->end - this->start;
    if (solutionFound)
    {
        cout << "Solution computed with " << this->expancoes << " nodes searched" << endl;
        cout << "Solution with " << this->best_move.size() << " movements" << endl;
        cout << "Solution took " << elapsed.count() << " seconds" << endl;

        cout << "Press ENTER to continue" << endl;

        cin.get();
    }
    return solutionFound;
}

bool AI::alreadyBeenOn(vector<pair<vector<pair<u_int, u_int>>, u_int>> visited, u_int max_search, u_int i, pair<u_int, u_int> position, vector<pair<u_int, u_int>> robot_positions)
{
    if (!this->evitar_ciclos)
        return false;
    u_int conta;
    for (u_int j = 0; j < visited.size(); j++)
    {
        if (visited[j].second >= max_search)
            continue;
        if (position.first == visited[j].first[i].first && position.second == visited[j].first[i].second)
        {
            conta = 1;
            for (u_int k = 0; k < visited[j].first.size(); k++)
            {
                if (i == k)
                    continue;
                if (robot_positions[k].first == visited[j].first[k].first && robot_positions[k].second == visited[j].first[k].second)
                {
                    conta++;
                }
            }
            if (conta == visited[j].first.size())
                return true;
        }
    }
    return false;
}

bool AI::dfs()
{
    vector<pair<vector<pair<u_int, u_int>>, u_int>> visited;
    visited.push_back(make_pair(this->robot_positions, 0));
    vector<pair<u_int, char>> moves;
    this->best_move.clear();
    this->best_custo = INT_MAX;
    cout << "Limite maximo de pesquisa: ";
    cin >> this->limite;
    char lido;
    cout << "Quer evitar repeticoes?(Y/N) ";
    cin >> lido;
    if (lido == 'Y' || lido == 'y')
        this->evitar_ciclos = true;
    else
        this->evitar_ciclos = false;
    cout << "Searching ..." << endl;
    this->expancoes = 0;
    this->start = chrono::high_resolution_clock::now();
    return this->dfs(1, this->map_char, this->robot_positions, visited, moves);
}

bool AI::dfs(int custo, vector<vector<char>> map_char, vector<pair<u_int, u_int>> robot_positions, vector<pair<vector<pair<u_int, u_int>>, u_int>> &visited, vector<pair<u_int, char>> moves)
{
    if (custo > (int)this->limite)
        return false;

    for (u_int i = 0; i < robot_positions.size(); i++)
    {
        pair<u_int, u_int> current_position = robot_positions[i];

        pair<u_int, u_int> top_move = this->MoveTop(map_char, i, robot_positions);

        if (top_move != current_position && !this->alreadyBeenOn(visited, custo, i, top_move, robot_positions))
        {
            this->expancoes++;
            vector<pair<u_int, u_int>> copy_robot_positions = robot_positions;
            vector<pair<u_int, char>> copy_moves = moves;
            vector<vector<char>> copy_map_char = map_char;
            copy_moves.push_back(make_pair(i, 't'));
            this->replacePosition(i, current_position, top_move, copy_robot_positions, copy_map_char);
            if (this->checkEndGame(copy_robot_positions))
            {
                this->best_custo = custo;
                this->best_move = copy_moves;
                return true;
            }
            visited.push_back(make_pair(copy_robot_positions, custo));
            if (this->dfs(custo + 1, copy_map_char, copy_robot_positions, visited, copy_moves))
                return true; //houve_sol = true;
        }
        pair<u_int, u_int> left_move = this->MoveLeft(map_char, i, robot_positions);
        if (left_move != current_position && !this->alreadyBeenOn(visited, custo, i, left_move, robot_positions))
        {
            this->expancoes++;
            vector<pair<u_int, u_int>> copy_robot_positions = robot_positions;
            vector<pair<u_int, char>> copy_moves = moves;
            vector<vector<char>> copy_map_char = map_char;
            copy_moves.push_back(make_pair(i, 'l'));
            this->replacePosition(i, current_position, left_move, copy_robot_positions, copy_map_char);
            if (this->checkEndGame(copy_robot_positions))
            {
                this->best_custo = custo;
                this->best_move = copy_moves;
                return true;
            }
            visited.push_back(make_pair(copy_robot_positions, custo));
            if (this->dfs(custo + 1, copy_map_char, copy_robot_positions, visited, copy_moves))
                return true; //houve_sol = true;
        }
        pair<u_int, u_int> bottom_move = this->MoveBottom(map_char, i, robot_positions);
        if (bottom_move != current_position && !this->alreadyBeenOn(visited, custo, i, bottom_move, robot_positions))
        {
            this->expancoes++;
            vector<pair<u_int, u_int>> copy_robot_positions = robot_positions;
            vector<pair<u_int, char>> copy_moves = moves;
            vector<vector<char>> copy_map_char = map_char;
            copy_moves.push_back(make_pair(i, 'b'));
            this->replacePosition(i, current_position, bottom_move, copy_robot_positions, copy_map_char);
            if (this->checkEndGame(copy_robot_positions))
            {
                this->best_custo = custo;
                this->best_move = copy_moves;
                return true;
            }
            visited.push_back(make_pair(copy_robot_positions, custo));
            if (this->dfs(custo + 1, copy_map_char, copy_robot_positions, visited, copy_moves))
                return true; // houve_sol = true;
        }
        pair<u_int, u_int> right_move = this->MoveRight(map_char, i, robot_positions);
        if (right_move != current_position && !this->alreadyBeenOn(visited, custo, i, right_move, robot_positions))
        {
            this->expancoes++;
            vector<pair<u_int, u_int>> copy_robot_positions = robot_positions;
            vector<pair<u_int, char>> copy_moves = moves;
            vector<vector<char>> copy_map_char = map_char;
            copy_moves.push_back(make_pair(i, 'r'));
            this->replacePosition(i, current_position, right_move, copy_robot_positions, copy_map_char);
            if (this->checkEndGame(copy_robot_positions))
            {
                this->best_custo = custo;
                this->best_move = copy_moves;
                return true;
            }
            visited.push_back(make_pair(copy_robot_positions, custo));
            if (this->dfs(custo + 1, copy_map_char, copy_robot_positions, visited, copy_moves))
                return true; //houve_sol = true;
        }
    }
    return false;
}

bool AI::iterativeDfs()
{
    vector<pair<vector<pair<u_int, u_int>>, u_int>> visited;
    visited.push_back(make_pair(this->robot_positions, 0));
    vector<pair<u_int, char>> moves;
    this->best_move.clear();
    this->best_custo = INT_MAX;
    this->evitar_ciclos = true;
    this->limite = 1;
    u_int max_limite;
    cout << "Limite maximo: ";
    cin >> max_limite;
    this->start = chrono::high_resolution_clock::now();
    cout << "Limite atual: " << this->limite << endl;
    while (!this->dfs(1, this->map_char, this->robot_positions, visited, moves))
    {
        this->limite++;
        if (this->limite > max_limite)
            return false;
        visited.clear();
        visited.push_back(make_pair(this->robot_positions, 0));
        this->best_move.clear();
        this->best_custo = INT_MAX;
        cout << "Limite atual: " << this->limite << endl;
    }
    return true;
}

bool AI::astar()
{
    Node *current = nullptr;
    set<Node *> openSet, closedSet;
    openSet.insert(new Node(this->robot_positions, this->map_char));

    while (!openSet.empty())
    {
        current = *openSet.begin();
        this->expancoes++;

        for (auto node : openSet)
        {
            if (node->getScore() <= current->getScore())
            {

                current = node;
            }
        }
        if (this->checkEndGame(current->robotsCoords))
        {
            break;
        }
        closedSet.insert(current);
        openSet.erase(std::find(openSet.begin(), openSet.end(), current));

        for (u_int i = 0; i < this->robot_positions.size(); ++i)
        {
            for (int j = 0; j < 4; j++)
            {
                pair<u_int, u_int> newCoordinates = getNewCoords(i, j, current);
                vector<vector<char>> new_char_map = current->map_char;
                vector<pair<u_int, u_int>> newRobotCoords = current->robotsCoords;
                this->replacePosition(i, current->robotsCoords[i], newCoordinates, newRobotCoords, new_char_map);
                if (detectCollision(current->robotsCoords[i], newCoordinates) ||
                    findNodeOnList(closedSet, newRobotCoords))
                {
                    continue;
                }

                u_int totalCost = current->G + 1;

                Node *successor = findNodeOnList(openSet, newRobotCoords);
                if (successor == nullptr)
                {
                    successor = new Node(newRobotCoords, new_char_map, current);
                    successor->move = pair<u_int, char>(i, numToPlay(j));
                    successor->G = totalCost;
                    successor->computeHeuristic(this->map->getRobotTargets(this->level));

                    openSet.insert(successor);
                }
                else if (totalCost < successor->G)
                {
                    successor->parent = current;
                    successor->G = totalCost;
                    successor->move = pair<u_int, char>(i, numToPlay(j));
                }
            }
        }
    }
    if (!this->checkEndGame(current->robotsCoords))
    {
        return false;
    }
    while (current != nullptr)
    {
        if (current->move.second != 'f')
        {
            this->best_move.insert(this->best_move.begin(), current->move);
        }
        current = current->parent;
    }
    releaseNodes(openSet);
    releaseNodes(closedSet);

    return true;
}

bool AI::greedy()
{
    Node *current = nullptr;
    set<Node *> openSet, closedSet;
    openSet.insert(new Node(this->robot_positions, this->map_char));

    while (!openSet.empty())
    {
        current = *openSet.begin();

        for (auto node : openSet)
        {
            if (node->getScore() <= current->getScore())
            {

                current = node;
            }
        }
        if (this->checkEndGame(current->robotsCoords))
        {
            break;
        }
        closedSet.insert(current);
        openSet.erase(std::find(openSet.begin(), openSet.end(), current));
        for (u_int i = 0; i < this->robot_positions.size(); ++i)
        {
            for (int j = 0; j < 4; j++)
            {
                pair<u_int, u_int> newCoordinates = getNewCoords(i, j, current);
                vector<vector<char>> new_char_map = current->map_char;
                vector<pair<u_int, u_int>> newRobotCoords = current->robotsCoords;
                this->replacePosition(i, current->robotsCoords[i], newCoordinates, newRobotCoords, new_char_map);
                if (detectCollision(current->robotsCoords[i], newCoordinates) ||
                    findNodeOnList(closedSet, newRobotCoords))
                {
                    continue;
                }

                Node *successor = findNodeOnList(openSet, newRobotCoords);
                if (successor == nullptr)
                {
                    successor = new Node(newRobotCoords, new_char_map, current);
                    successor->move = pair<u_int, char>(i, numToPlay(j));
                    successor->computeHeuristic(this->map->getRobotTargets(this->level));

                    openSet.insert(successor);
                }
            }
        }
    }
    if (!this->checkEndGame(current->robotsCoords))
    {
        return false;
    }
    while (current != nullptr)
    {
        if (current->move.second != 'f')
        {
            this->best_move.insert(this->best_move.begin(), current->move);
        }
        current = current->parent;
    }
    releaseNodes(openSet);
    releaseNodes(closedSet);

    return true;
}

pair<u_int, u_int> AI::getNewCoords(int robotIndex, int direction, Node *node)
{
    pair<u_int, u_int> newCoords;
    switch (direction)
    {
    case 0:
        newCoords = this->MoveTop(node->map_char, robotIndex, node->robotsCoords);

        break;
    case 1:
        newCoords = this->MoveLeft(node->map_char, robotIndex, node->robotsCoords);

        break;
    case 2:
        newCoords = this->MoveBottom(node->map_char, robotIndex, node->robotsCoords);

        break;
    case 3:
        newCoords = this->MoveRight(node->map_char, robotIndex, node->robotsCoords);

        break;
    }
    return newCoords;
}

Node *AI::findNodeOnList(set<Node *> &nodes, vector<pair<u_int, u_int>> robotsCoords)
{
    for (auto node : nodes)
    {
        if (node->robotsCoords == robotsCoords)
        {
            return node;
        }
    }
    return nullptr;
}

void AI::releaseNodes(set<Node *> &nodes)
{
    for (auto it = nodes.begin(); it != nodes.end();)
    {
        delete *it;
        it = nodes.erase(it);
    }
}

bool AI::detectCollision(pair<u_int, u_int> oldCoords, pair<u_int, u_int> newCoords)
{
    if ((oldCoords.first == newCoords.first) && (oldCoords.second == newCoords.second))
    {
        return true;
    }
    return false;
}

char AI::numToPlay(int num)
{
    char play = 's';
    switch (num)
    {
    case 0:
        play = 't';
        break;
    case 1:
        play = 'l';
        break;
    case 2:
        play = 'b';
        break;
    case 3:
        play = 'r';
        break;
    }
    return play;
}

bool AI::bfs()
{
    queue<pair<vector<pair<u_int, u_int>>, vector<pair<u_int, char>>>> myqueue;
    vector<pair<u_int, char>> moves;
    vector<pair<vector<pair<u_int, u_int>>, u_int>> visited;
    myqueue.push(make_pair(this->robot_positions, moves));
    u_int profundidade = 1;

    while (!myqueue.empty())
    {
        if (this->checkEndGame(myqueue.front().first))
        {
            this->best_custo = profundidade;
            this->best_move = myqueue.front().second;
            break;
        }

        vector<pair<u_int, u_int>> current_positions = myqueue.front().first;
        visited.push_back(make_pair(current_positions, 0));
        vector<pair<u_int, char>> current_moves = myqueue.front().second;
        if (profundidade != myqueue.front().second.size())
        {
            profundidade = myqueue.front().second.size();
            cout << myqueue.front().second.size() << endl;
        }
        myqueue.pop();
        this->expancoes++;

        vector<vector<char>> char_map = this->map->getCharMap(this->level, current_positions);

        for (u_int i = 0; i < current_positions.size(); i++)
        {
            pair<u_int, u_int> position = current_positions[i];

            pair<u_int, u_int> top_move = this->MoveTop(char_map, i, current_positions);
            if (top_move != position && !this->alreadyBeenOn(visited, profundidade, i, top_move, current_positions))
            {
                vector<pair<u_int, u_int>> robot_positions_new = current_positions;
                vector<pair<u_int, char>> current_moves_new = current_moves;
                current_moves_new.push_back(make_pair(i, 't'));
                robot_positions_new[i] = top_move;
                myqueue.push(make_pair(robot_positions_new, current_moves_new));
                visited.push_back(make_pair(robot_positions_new, profundidade));
            }
            pair<u_int, u_int> bottom_move = this->MoveBottom(char_map, i, current_positions);
            if (bottom_move != position && !this->alreadyBeenOn(visited, profundidade, i, bottom_move, current_positions))
            {
                vector<pair<u_int, u_int>> robot_positions_new = current_positions;
                vector<pair<u_int, char>> current_moves_new = current_moves;
                current_moves_new.push_back(make_pair(i, 'b'));
                robot_positions_new[i] = bottom_move;
                myqueue.push(make_pair(robot_positions_new, current_moves_new));
                visited.push_back(make_pair(robot_positions_new, profundidade));
            }
            pair<u_int, u_int> left_move = this->MoveLeft(char_map, i, current_positions);
            if (left_move != position && !this->alreadyBeenOn(visited, profundidade, i, left_move, current_positions))
            {
                vector<pair<u_int, u_int>> robot_positions_new = current_positions;
                vector<pair<u_int, char>> current_moves_new = current_moves;
                current_moves_new.push_back(make_pair(i, 'l'));
                robot_positions_new[i] = left_move;
                myqueue.push(make_pair(robot_positions_new, current_moves_new));
                visited.push_back(make_pair(robot_positions_new, profundidade));
            }
            pair<u_int, u_int> right_move = this->MoveRight(char_map, i, current_positions);
            if (right_move != position && !this->alreadyBeenOn(visited, profundidade, i, right_move, current_positions))
            {
                vector<pair<u_int, u_int>> robot_positions_new = current_positions;
                vector<pair<u_int, char>> current_moves_new = current_moves;
                current_moves_new.push_back(make_pair(i, 'r'));
                robot_positions_new[i] = right_move;
                myqueue.push(make_pair(robot_positions_new, current_moves_new));
                visited.push_back(make_pair(robot_positions_new, profundidade));
            }
        }
    }

    return true;
}

void AI::TranslateToBestMove(Node *node)
{

    this->best_move.clear();

    while (node != nullptr)
    {
        if (node->move.second != 'f')
        {
            this->best_move.insert(this->best_move.begin(), node->move);
        }
        node = node->parent;
    }
}

bool AI::astartSecond()
{
    list<Info> q;
    q.clear();
    vector<pair<u_int, char>> moves_tmp;
    Info novo;
    novo.cost = 0;
    novo.pos = this->robot_positions;
    novo.moves = moves_tmp;
    q.push_back(novo);
    vector<vector<pair<u_int, u_int>>> visited;

    while (!q.empty())
    {
        Info selected = this->bestOption(q);
        vector<pair<u_int, u_int>> pos = selected.pos;
        visited.push_back(pos);
        vector<pair<u_int, char>> moves = selected.moves;
        long int custo = moves.size();
        this->expancoes++;
        if (this->checkEndGame(pos))
        {

            this->best_custo = moves.size();
            this->best_move = moves;
            return true;
        }
        vector<vector<char>> char_map = this->map->getCharMap(this->level, pos);
        for (u_int i = 0; i < pos.size(); i++)
        {

            pair<u_int, u_int> current_position = pos[i];

            pair<u_int, u_int> top_move = this->MoveTop(char_map, i, pos);
            if (top_move != current_position && !this->alreadyBeenOn(visited, i, top_move, pos))
            {
                Info novo;
                novo.pos = pos;
                novo.moves = moves;
                novo.pos[i] = top_move;
                novo.cost = custo + 1 + this->computeHeuristic(novo.pos, this->map->getRobotTargets(this->level));
                novo.moves.push_back(make_pair(i, 't'));
                if (!this->rep(q, novo))
                    q.push_back(novo);
            }
            pair<u_int, u_int> bottom_move = this->MoveBottom(char_map, i, pos);
            if (bottom_move != current_position && !this->alreadyBeenOn(visited, i, bottom_move, pos))
            {
                Info novo;
                novo.pos = pos;
                novo.moves = moves;
                novo.pos[i] = bottom_move;
                novo.cost = custo + 1 + this->computeHeuristic(novo.pos, this->map->getRobotTargets(this->level));
                novo.moves.push_back(make_pair(i, 'b'));
                if (!this->rep(q, novo))
                    q.push_back(novo);
            }
            pair<u_int, u_int> left_move = this->MoveLeft(char_map, i, pos);
            if (left_move != current_position && !this->alreadyBeenOn(visited, i, left_move, pos))
            {
                Info novo;
                novo.pos = pos;
                novo.moves = moves;
                novo.pos[i] = left_move;
                novo.cost = custo + 1 + this->computeHeuristic(novo.pos, this->map->getRobotTargets(this->level));
                novo.moves.push_back(make_pair(i, 'l'));
                if (!this->rep(q, novo))
                    q.push_back(novo);
            }
            pair<u_int, u_int> right_move = this->MoveRight(char_map, i, pos);
            if (right_move != current_position && !this->alreadyBeenOn(visited, i, right_move, pos))
            {
                Info novo;
                novo.pos = pos;
                novo.moves = moves;
                novo.pos[i] = right_move;
                novo.cost = custo + 1 + this->computeHeuristic(novo.pos, this->map->getRobotTargets(this->level));
                novo.moves.push_back(make_pair(i, 'r'));
                if (!this->rep(q, novo))
                    q.push_back(novo);
            }
        }
    }
    return false;
}

long int AI::computeHeuristic(vector<pair<u_int, u_int>> robot_pos, vector<pair<u_int, u_int>> targets)
{
    long int h = 0;
    int deltaX, deltaY;
    for (unsigned int i = 0; i < targets.size(); i++)
    {
        deltaX = abs(((int)(robot_pos[i].first)) - ((int)(targets[i].first)));
        deltaY = abs(((int)(robot_pos[i].second)) - ((int)(targets[i].second)));
        if (deltaX != 0)
        {
            h++;
        }
        if (deltaY != 0)
        {
            h++;
        }
    }
    return h;
}

Info AI::bestOption(list<Info> &list)
{
    int best = INT_MAX;
    std::list<Info>::iterator devolver;
    for (std::list<Info>::iterator it = list.begin(); it != list.end(); ++it)
    {
        if (it->cost < best)
        {
            best = it->cost;
            devolver = it;
        }
    }
    Info guardar = *devolver;
    list.erase(devolver);
    return guardar;
}

bool AI::rep(std::list<Info> &list, Info testar)
{
    for (std::list<Info>::iterator it = list.begin(); it != list.end(); ++it)
    {
        if (it->pos == testar.pos)
        {
            if (testar.cost < it->cost)
            {
                it->cost = testar.cost;
                it->pos = testar.pos;
                it->moves = testar.moves;
            }
            return true;
        }
    }
    return false;
}

bool AI::alreadyBeenOn(vector<vector<pair<u_int, u_int>>> visited, u_int i, pair<u_int, u_int> position, vector<pair<u_int, u_int>> robot_positions)
{
    bool conta;
    for (u_int j = 0; j < visited.size(); j++)
    {
        if (position.first == visited[j][i].first && position.second == visited[j][i].second)
        {
            conta = true;
            for (u_int k = 0; k < visited[j].size(); k++)
            {
                if (i == k)
                    continue;
                if (!(robot_positions[k].first == visited[j][k].first && robot_positions[k].second == visited[j][k].second))
                {
                    conta = false;
                    break;
                }
            }
            if (conta)
                return true;
        }
    }
    return false;
}