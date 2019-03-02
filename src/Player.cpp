#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

Player::Player(){
}

string Player::play(){
    cout << "Play: ";
    string line;
    getline(cin,line);
    return line;
}