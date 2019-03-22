#include "AI.h"

using namespace std;

AI::AI(int level, Map *map) : Player(level, map) {}

bool AI::makeMove()
{
    this->map->printMap(this->level, this->robot_positions);
    if (!this->alg_calculated)
    {
        if (this->dfs())
        {
            this->alg_calculated = true;
            this->index_sol = 0;
        }
        else
        {
            cout << "Não foi possivel encontrar uma solução " << endl;
            return false;
        }
    }
    if (this->alg_calculated)
    {
        if (this->index_sol >= this->best_move.size())
        {
            this->map->printMap(this->level, this->robot_positions);
            this->alg_calculated=false;
            return false;
        }
        u_int robot_number=this->best_move[this->index_sol].first;
        char direction =this->best_move[this->index_sol].second;
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
            this->alg_calculated=false;
            return false;
        }
    }
    return true;
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