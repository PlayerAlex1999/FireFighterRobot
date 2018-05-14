#ifndef ROBOT_H
#define ROBOT_H

#include "includes.h"

#define TILE_ROBOT 'R'
#define TILE_ROBOT_WITH_EXTINGUISHER 'P'

#define DEFAULT_HP 10


s_robot initRobot(int x, int y);
char displayRobot(s_robot* robot);
int isAtPos(s_robot* robot, int x, int y);

vector getPath(s_room* room, s_pos dest);
int mustBeIgnored(vector* op, vector* cl, s_node* node);
void addToRobotVision(s_room* room, s_pos pos);
int moveTo(s_room* room, vector* vect);

#endif
