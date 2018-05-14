#ifndef ROOM_H
#define ROOM_H

#include "includes.h"

#define DEFAULT_ROOM "./plans/plan1.txt"

s_room loadRoom(char* mapFilename);
void displayRoom(s_room room);

#endif
