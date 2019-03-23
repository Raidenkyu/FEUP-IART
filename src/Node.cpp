# include "Node.h"

using namespace std;

Node::Node(vector<pair<u_int,u_int>> robotsCoords,Node * parent):
    G(0),
    H(0),
    parent(parent),
    move(pair<u_int,char>('f',0))
    {

    }

u_int Node::getScore(){
    return (G+H);
}


u_int Node::computeHeuristic(vector<pair<u_int,u_int>> targets){
    u_int h = 0;
    for(unsigned int i = 0; i < targets.size(); i++){
        h+= abs(((int)robotsCoords[i].first) - ((int)targets[i].first));
        h+= abs(((int)robotsCoords[i].second) - ((int)targets[i].second));
    }
    this->H = 0;
    return h;
}