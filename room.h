#ifndef ROOM_H
#define ROOM_H

#include "includes.h"
#include "robot.h"

#define DEFAULT_ROOM "./plans/plan1.txt"
#define TILE_WALL 'X'
#define TILE_START 'D'
#define TILE_EXTINGUISHER 'E'
#define TILE_FIRE_LVL1 '1'
#define TILE_FIRE_LVL2 '2'
#define TILE_FIRE_LVL3 '3'


s_room loadRoom(char* mapFilename);
void displayRoom(s_room* room);

#endif
