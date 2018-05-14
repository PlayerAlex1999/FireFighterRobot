#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_pos {
  int x,y;
} s_pos;

typedef struct s_room {
  int sizeX, sizeY;
  char** tiles;

  s_pos extinguisher;
}

#endif
