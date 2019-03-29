# include "Node.h"

using namespace std;

Node::Node(vector<pair<u_int,u_int>> robotsCoords,vector<vector<char>> map_char,Node * parent):
    G(0),
    H(0),
    robotsCoords(robotsCoords),
    parent(parent),
    move(pair<u_int,char>(0,'f')),
    map_char(map_char)
    {

    }

u_int Node::getScore(){
    return (G+H);
}


u_int Node::computeHeuristic(vector<pair<u_int,u_int>> targets){
    u_int h = 0;
    int deltaX, deltaY;
    for(unsigned int i = 0; i < targets.size(); i++){
        deltaX= abs(((int)(robotsCoords[i].first)) - ((int)(targets[i].first)));
        deltaY= abs(((int)(robotsCoords[i].second)) - ((int)(targets[i].second)));
        if(deltaX != 0){
            h++;
        }
        if(deltaY != 0){
            h++;
        }
    }
    this->H = h;
    return h;
}