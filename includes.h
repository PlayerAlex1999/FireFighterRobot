#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef enum e_direction {
  UP, RIGHT, DOWN, LEFT
} e_direction;

typedef struct s_pos {
  int x,y;
} s_pos;

typedef struct s_robot {
  s_pos pos;
  int healthPoints;

  int hasExtinguisher;
  s_pos firePosition;
} s_robot;

typedef struct s_room {
  int sizeX, sizeY;
  char** tiles;

  s_pos startPos;
  s_pos extinguisherPos;

  s_robot robot;
} s_room;

#endif
