#include "AI.h"
#include <algorithm>
#include <queue>

using namespace std;

AI::AI(int level, Map *map, int algorithm) : Player(level, map),
                                             algorithm(algorithm)
{

    if (this->computeSolution())
    {
        this->alg_calculated = true;
    }
    this->index_sol=0;
}

bool AI::makeMove()
{

    this->map->printMap(this->level, this->robot_positions);
    cout << "Press ENTER to get next step" << endl;

    cin.get();

    if (this->alg_calculated)
    {
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
    return true;
}

bool AI::computeSolution()
{
    bool solutionFound = false;
    this->map->printMap(this->level, this->robot_positions);
    cout << "Computing a Solution. Wait a few seconds" << endl;
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
    default:
        cout << "Invalid Algorithm" << endl;
        exit(0);
    }
    cout << "Solution computed" << endl;
    return solutionFound;
}

bool AI::alreadyBeenOn(std::vector<std::pair<u_int, u_int>> visited, std::pair<u_int, u_int> position)
{
    for (int i = (int)visited.size() - 1; i >= 0; i--)
    {
        if (position.first == visited[i].first && position.second == visited[i].second)
        {
            return true;
        }
    }
    return false;
}

bool AI::dfs()
{
    vector<vector<pair<u_int, u_int>>> visited;
    for (u_int i = 0; i < this->robot_positions.size(); i++)
    {
        vector<pair<u_int, u_int>> temp;
        visited.push_back(temp);
    }
    vector<pair<u_int, char>> moves;
    this->best_move.clear();
    this->best_custo = INT_MAX;
    return this->dfs(1, this->map_char, this->robot_positions, visited, moves);
}

bool AI::dfs(int custo, vector<vector<char>> map_char, vector<pair<u_int, u_int>> robot_positions, vector<vector<pair<u_int, u_int>>> visited, vector<pair<u_int, char>> moves)
{
    if (custo > 20)
        return false;

    bool houve_sol = false;
    if (custo >= this->best_custo)
        return false;
    for (u_int i = 0; i < robot_positions.size(); i++)
    {
        pair<u_int, u_int> current_position = robot_positions[i];

        pair<u_int, u_int> top_move = this->MoveTop(map_char, i, robot_positions);
        pair<u_int, u_int> bottom_move = this->MoveBottom(map_char, i, robot_positions);
        pair<u_int, u_int> left_move = this->MoveLeft(map_char, i, robot_positions);
        pair<u_int, u_int> right_move = this->MoveRight(map_char, i, robot_positions);

        if (top_move != current_position && !this->alreadyBeenOn(visited[i], top_move))
        {
            vector<pair<u_int, u_int>> copy_robot_positions = robot_positions;
            vector<vector<pair<u_int, u_int>>> copy_visited = visited;
            vector<pair<u_int, char>> copy_moves = moves;
            vector<vector<char>> copy_map_char = map_char;
            copy_moves.push_back(make_pair(i, 't'));
            copy_visited[i].push_back(current_position);
            this->replacePosition(i, current_position, top_move, copy_robot_positions, copy_map_char);
            if (custo < this->best_custo && this->checkEndGame(copy_robot_positions))
            {
                this->best_custo = custo;
                this->best_move = copy_moves;
                return true;
            }
            if (this->dfs(custo + 1, copy_map_char, copy_robot_positions, copy_visited, copy_moves))
                houve_sol = true;
        }
        if (bottom_move != current_position && !this->alreadyBeenOn(visited[i], bottom_move))
        {
            vector<pair<u_int, u_int>> copy_robot_positions = robot_positions;
            vector<vector<pair<u_int, u_int>>> copy_visited = visited;
            vector<pair<u_int, char>> copy_moves = moves;
            vector<vector<char>> copy_map_char = map_char;
            copy_moves.push_back(make_pair(i, 'b'));
            copy_visited[i].push_back(current_position);
            this->replacePosition(i, current_position, bottom_move, copy_robot_positions, copy_map_char);
            if (custo < this->best_custo && this->checkEndGame(copy_robot_positions))
            {
                this->best_custo = custo;
                this->best_move = copy_moves;
                return true;
            }
            if (this->dfs(custo + 1, copy_map_char, copy_robot_positions, copy_visited, copy_moves))
                houve_sol = true;
        }
        if (left_move != current_position && !this->alreadyBeenOn(visited[i], left_move))
        {
            vector<pair<u_int, u_int>> copy_robot_positions = robot_positions;
            vector<vector<pair<u_int, u_int>>> copy_visited = visited;
            vector<pair<u_int, char>> copy_moves = moves;
            vector<vector<char>> copy_map_char = map_char;
            copy_moves.push_back(make_pair(i, 'l'));
            copy_visited[i].push_back(current_position);
            this->replacePosition(i, current_position, left_move, copy_robot_positions, copy_map_char);
            if (custo < this->best_custo && this->checkEndGame(copy_robot_positions))
            {
                this->best_custo = custo;
                this->best_move = copy_moves;
                return true;
            }
            if (this->dfs(custo + 1, copy_map_char, copy_robot_positions, copy_visited, copy_moves))
                houve_sol = true;
        }
        if (right_move != current_position && !this->alreadyBeenOn(visited[i], right_move))
        {
            vector<pair<u_int, u_int>> copy_robot_positions = robot_positions;
            vector<vector<pair<u_int, u_int>>> copy_visited = visited;
            vector<pair<u_int, char>> copy_moves = moves;
            vector<vector<char>> copy_map_char = map_char;
            copy_moves.push_back(make_pair(i, 'r'));
            copy_visited[i].push_back(current_position);
            this->replacePosition(i, current_position, right_move, copy_robot_positions, copy_map_char);
            if (custo < this->best_custo && this->checkEndGame(copy_robot_positions))
            {
                this->best_custo = custo;
                this->best_move = copy_moves;
                return true;
            }
            if (this->dfs(custo + 1, copy_map_char, copy_robot_positions, copy_visited, copy_moves))
                houve_sol = true;
        }
    }
    return houve_sol;
}

bool AI::astar()
{
    Node *current = nullptr;
    set<Node *> openSet, closedSet;
    openSet.insert(new Node(this->robot_positions));

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
                pair<u_int, u_int> newCoordinates = getNewCoords(i, j, current->robotsCoords);
                vector<pair<u_int, u_int>> newRobotCoords = current->robotsCoords;
                newRobotCoords[i] = newCoordinates;
                if (detectCollision(current->robotsCoords[i], newCoordinates) ||
                    findNodeOnList(closedSet, newRobotCoords))
                {
                    continue;
                }

                u_int totalCost = current->G + 1;

                Node *successor = findNodeOnList(openSet, newRobotCoords);
                if (successor == nullptr)
                {
                    successor = new Node(newRobotCoords, current);
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

    return (this->best_move.size() > 0 ? true : false);
}

pair<u_int, u_int> AI::getNewCoords(int robotIndex, int direction, vector<pair<u_int, u_int>> robotsCoords)
{
    pair<u_int, u_int> newCoords;
    switch (direction)
    {
    case 0:
        newCoords = this->MoveTop(this->map_char, robotIndex, robotsCoords);

        break;
    case 1:
        newCoords = this->MoveLeft(map_char, robotIndex, robotsCoords);

        break;
    case 2:
        newCoords = this->MoveBottom(map_char, robotIndex, robotsCoords);

        break;
    case 3:
        newCoords = this->MoveRight(map_char, robotIndex, robotsCoords);

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
    queue<pair<vector<pair<u_int,u_int>>,vector<pair<u_int, char>>>> myqueue;
    vector<pair<u_int, char>> moves;
    myqueue.push(make_pair(this->robot_positions,moves));
    u_int custo=0;
    u_int profundidade=1;
    
    while (!myqueue.empty())
    {
        if (this->checkEndGame(myqueue.front().first))
        {
            this->best_custo=custo;
            this->best_move=myqueue.front().second;
            break;
        }
        vector<pair<u_int, u_int>> current_positions = myqueue.front().first;
        vector<pair<u_int, char>> current_moves = myqueue.front().second;
        if(profundidade!=myqueue.front().second.size())
        {
            profundidade=myqueue.front().second.size();
            cout << myqueue.front().second.size() << endl;
        }
        myqueue.pop();

        vector<vector<char>> char_map=this->map->getCharMap(this->level,current_positions);
        
        for (u_int i = 0; i < current_positions.size(); i++)
        {
            pair<u_int, u_int> position=current_positions[i];
        
            pair<u_int, u_int> top_move = this->MoveTop(char_map, i, current_positions);
            pair<u_int, u_int> bottom_move = this->MoveBottom(char_map, i, current_positions);
            pair<u_int, u_int> left_move = this->MoveLeft(char_map, i, current_positions);
            pair<u_int, u_int> right_move = this->MoveRight(char_map, i, current_positions);

            if (top_move != position)
            {
                vector<pair<u_int, u_int>> robot_positions_new = current_positions;
                vector<pair<u_int, char>> current_moves_new = current_moves;
                current_moves_new.push_back(make_pair(i, 't'));
                robot_positions_new[i] = top_move;
                myqueue.push(make_pair(robot_positions_new,current_moves_new));
                //cout << "Robot: "<< i << "Top" << top_move.first << top_move.second << endl;
            }
            if (bottom_move != position)
            {
                vector<pair<u_int, u_int>> robot_positions_new = current_positions;
                vector<pair<u_int, char>> current_moves_new = current_moves;
                current_moves_new.push_back(make_pair(i, 'b'));
                robot_positions_new[i] = bottom_move;
                myqueue.push(make_pair(robot_positions_new,current_moves_new));
                //cout << "Robot: "<< i << "Bottom" << bottom_move.first << bottom_move.second << endl;
            }
            if (left_move != position)
            {
                vector<pair<u_int, u_int>> robot_positions_new = current_positions;
                vector<pair<u_int, char>> current_moves_new = current_moves;
                current_moves_new.push_back(make_pair(i, 'l'));
                robot_positions_new[i] = left_move;
                myqueue.push(make_pair(robot_positions_new,current_moves_new));
                //cout << "Robot: "<< i << "Left" << left_move.first << left_move.second << endl;
            }
            if (right_move != position)
            {
                vector<pair<u_int, u_int>> robot_positions_new = current_positions;
                vector<pair<u_int, char>> current_moves_new = current_moves;
                current_moves_new.push_back(make_pair(i, 'r'));
                robot_positions_new[i] = right_move;
                myqueue.push(make_pair(robot_positions_new,current_moves_new));
                //cout << "Robot: "<< i << "Right" << right_move.first << right_move.second << endl;
            }
        }
        //cout << "Front: "<< myqueue.front()->robotsCoords[0].first << myqueue.front()->robotsCoords[0].second << endl;
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
    /* cout << "Move 0: " << node->move.first << node->move.second << endl;
int i = 1;
    while(node->parent != nullptr){
    cout << node->parent << endl;
    cout << "Move " << i << ": " << node->move.first << node->move.second << endl;
    i++;
    this->best_move.push_back(node->);
    node = node->parent;
     */
    /*   }
    cin.get();
    for(unsigned int i = 0; i < this->best_move.size(); i++){
        cout << this->best_move[i].first << this->best_move[i].second << endl;
    }
    cin.get(); */
}