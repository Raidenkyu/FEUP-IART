#ifndef MAP_H_
#define MAP_H_

#include <vector>

class Map {
private:
    int num;
    std::vector<std::vector<char>> charMap;
public:
    Map(int level, std::vector<std::vector<char>> & charMap);
    std::vector<std::vector<char>> getMap();
};

#endif