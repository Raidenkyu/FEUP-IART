#include "Robot.h"

using namespace std;

Robot::Robot(char type) : type(type), x(-1), y(-1) {}
/*
void Robot::dfs(vector<std::vector<char>> map, pair<int, int> currentPos, int custo, vector<pair<int, int>> visited, vector<pair<int, int>> movesUntilNow)
{
    pair<int, int> topMove = this->MoveTop(map, currentPos);
    pair<int, int> bottomMove = this->MoveBottom(map, currentPos);
    pair<int, int> leftMove = this->MoveLeft(map, currentPos);
    pair<int, int> rightMove = this->MoveRight(map, currentPos);
    int houveMovement = 0;
    pair<int, int> topMoveTarget = make_pair(topMove.first-1,topMove.second);
    pair<int, int> bottomMoveTarget = make_pair(bottomMove.first+1,bottomMove.second);
    pair<int, int> leftMoveTarget = make_pair(leftMove.first,leftMove.second-1);
    pair<int, int> rightMoveTarget = make_pair(rightMove.first,rightMove.second+1);


    if (topMove != currentPos && !this->alreadyBeenOn(movesUntilNow, topMove))
    {
        movesUntilNow.push_back(topMove);
        visited.push_back(currentPos);
        currentPos = topMove;
        houveMovement++;
        this->dfs(map, currentPos, custo + 1, visited, movesUntilNow);
    }
    if (bottomMove != currentPos && !this->alreadyBeenOn(movesUntilNow, bottomMove))
    {
        movesUntilNow.push_back(bottomMove);
        visited.push_back(currentPos);
        currentPos = bottomMove;
        houveMovement++;
        this->dfs(map, currentPos, custo + 1, visited, movesUntilNow);
    }
    if (leftMove != currentPos && !this->alreadyBeenOn(movesUntilNow, leftMove))
    {
        movesUntilNow.push_back(leftMove);
        visited.push_back(currentPos);
        currentPos = leftMove;
        houveMovement++;
        this->dfs(map, currentPos, custo + 1, visited, movesUntilNow);
    }
    if (rightMove != currentPos && !this->alreadyBeenOn(movesUntilNow, rightMove))
    {
        movesUntilNow.push_back(rightMove);
        visited.push_back(currentPos);
        currentPos = rightMove;
        houveMovement++;
        this->dfs(map, currentPos, custo + 1, visited, movesUntilNow);
    }
    if (houveMovement == 0)
    {

        if (custo < this->minCusto && (topMoveTarget==this->target || bottomMoveTarget==this->target || leftMoveTarget==this->target || rightMoveTarget==this->target))
        {
            visited.push_back(currentPos);
            this->minCusto = custo;
            this->minVisited = visited;
        }
        return;
    }
}
bool Robot::moveDFS(std::vector<std::vector<char>> map)
{
    map[this->x][this->y] = ' ';
    vector<pair<int, int>> inicial;
    inicial.clear();
    vector<pair<int, int>> moves;
    moves.clear();
    this->minCusto = INT_MAX;
    this->minVisited.clear();
    this->dfs(map, make_pair(this->x, this->y), 0, inicial, moves);
    cout << this->minVisited.size() << endl;
    for(u_int i =0;i<this->minVisited.size();i++)
    {
        cout << this->minVisited[i].first << " " << this->minVisited[i].second << endl;
    }
    return true;
}

bool Robot::alreadyBeenOn(vector<pair<int, int>> visited, pair<int, int> pos)
{
    for (int i =(int)visited.size() - 1; i >= 0; i--)
    {
        if (pos.first == visited[i].first && pos.second == visited[i].second)
        {
            return true;
        }
    }
    return false;
}

bool Robot::move(char direction, vector<vector<char>> map)
{
    int xVector = 0;
    int yVector = 0;

    switch (direction)
    {
    case 'L':
        xVector = -1;
        break;
    case 'R':
        xVector = 1;
        break;
    case 'U':
        yVector = -1;
        break;
    case 'D':
        yVector = 1;
        break;

    default:
        return false;
    }

    while (map[this->getY() + yVector][this->getX() + xVector] == ' ')
    {

        this->x += xVector;
        this->y += yVector;
    }

    if (toupper(map[this->getY() + yVector][this->getX() + xVector]) == this->getType())
    {

        this->x += xVector;
        this->y += yVector;
        map[this->getY() + yVector][this->getX() + xVector] = this->getType();
    }
    return true;
}

void Robot::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Robot::getX()
{
    return this->x;
}

int Robot::getY()
{
    return this->y;
}

char Robot::getType()
{
    return this->type;
}*/