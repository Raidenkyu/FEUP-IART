#include "Map.h"

using namespace std;

Map::Map(int num, vector<vector<char>> & charMap): num(num),charMap(charMap) {

}

vector<vector<char>> Map::getMap(){
    return this->charMap;
}