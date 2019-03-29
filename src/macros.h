#ifndef MACROS_H_
#define MACROS_H_

#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <fstream>
#include <string>
#include <chrono>


typedef unsigned int u_int;

enum ALGORITHM{
    DFS, BFS, ASTAR, IDFS, GREEDY
};

#ifdef _WIN32 // To clear the screen depending in the User OS
#define clearScreen() system("cls");
#else
#define clearScreen() system("clear");
#endif

#endif