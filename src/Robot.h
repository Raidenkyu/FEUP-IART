#ifndef ROBOT_H_
#define ROBOT_H_


class Robot {
private: 
    unsigned int x,y;
    char type;
public:
    Robot(char type);
    bool move(char direction);
};

#endif