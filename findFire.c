#include "room.h"
#include "robot.h"

void setEmptyTilesInteresting(s_room* room) {
  for(int i=0; i<room->sizeX; i++)
    for(int j=0; j<room->sizeY; j++)
      if(room->nodes[j][i].robotVision == TILE_EMPTY)
        room->nodes[j][i].robotVision = TILE_POTENTIAL_FIRE;

  //Check if 3*3 interesting zone exist, set the interesting point in the center.
  for(int i=2; i<room->sizeX-2; i++)
    for(int j=2; j<room->sizeY-2; j++) {
      int pointFound = 1;

      for(int k=-1; k<=1; k++)
        for(int l=-1; l<=1; l++)
          if(room->nodes[j+k][i+l].robotVision != TILE_POTENTIAL_FIRE)
            pointFound =0;

      if(pointFound) {
        for(int k=-1; k<=1; k++)
          for(int l=-1; l<=1; l++)
            room->nodes[j+k][i+l].robotVision = TILE_EMPTY;

        room->nodes[j][i].robotVision = TILE_INTERESTING;
      }
    }

  //Check if 3*2 interesting zones exist, set the interesting point in the center;
  for(int i=2; i<room->sizeX-2; i++)
    for(int j=1; j<room->sizeY-1; j++) {
      int pointFound = 1;

      for(int k=0; k<=1; k++)
        for(int l=-1; l<=1; l++)
          if(room->nodes[j+k][i+l].robotVision != TILE_POTENTIAL_FIRE)
            pointFound=0;

      if(pointFound) {
        for(int k=0; k<=1; k++)
          for(int l=-1; l<=1; l++)
            room->nodes[j+k][i+l].robotVision = TILE_EMPTY;

        room->nodes[j][i].robotVision = TILE_INTERESTING;
      }
    }

  for(int i=1; i<room->sizeX-1; i++)
    for(int j=2; j<room->sizeY-2; j++) {
      int pointFound = 1;

      for(int k=-1; k<=1; k++)
        for(int l=0; l<=1; l++)
          if(room->nodes[j+k][i+l].robotVision != TILE_POTENTIAL_FIRE)
            pointFound=0;

      if(pointFound) {
        for(int k=-1; k<=1; k++)
          for(int l=0; l<=1; l++)
            room->nodes[j+k][i+l].robotVision = TILE_EMPTY;

        room->nodes[j][i].robotVision = TILE_INTERESTING;
      }
    }

  //Check if 2*2 interesting zones exist, set the interesting point in the center;
  for(int i=1; i<room->sizeX-1; i++)
    for(int j=1; j<room->sizeY-1; j++) {
      int pointFound = 1;

      for(int k=0; k<=1; k++)
        for(int l=0; l<=1; l++)
          if(room->nodes[j+k][i+l].robotVision != TILE_POTENTIAL_FIRE)
            pointFound = 0;

      if(pointFound) {
        for(int k=0; k<=1; k++)
          for(int l=0; l<=1; l++)
            room->nodes[j+k][i+l].robotVision = TILE_EMPTY;

        room->nodes[j][i].robotVision = TILE_INTERESTING;
      }
    }

  //Check if 5*1 or 3*1 interesting zones exist, set the interesting point in the center;
  for(int i=2; i<room->sizeX-2; i++)
    for(int j=1; j<room->sizeY-1; j++) {
      int pointFound = 1;

      for(int k=-2; k<=2; k++)
        if(room->nodes[j][i+k].robotVision != TILE_POTENTIAL_FIRE)
          pointFound = 0;

      if(pointFound) {
        for(int k=-2; k<=2; k++)
          room->nodes[j][i+k].robotVision = TILE_EMPTY;

        room->nodes[j][i].robotVision = TILE_INTERESTING;
      }
    }

  for(int i=1; i<room->sizeX-1; i++)
    for(int j=1; j<room->sizeY-1; j++) {
      int pointFound = 1;

      for(int k=-1; k<=1; k++)
        if(room->nodes[j][i+k].robotVision != TILE_POTENTIAL_FIRE)
          pointFound = 0;

      if(pointFound) {
        for(int k=-1; k<=1; k++)
          room->nodes[j][i+k].robotVision = TILE_EMPTY;

          room->nodes[j][i].robotVision = TILE_INTERESTING;
      }
  }


  for(int i=1; i<room->sizeX-1; i++)
    for(int j=2; j<room->sizeY-2; j++) {
      int pointFound = 1;

      for(int k=-2; k<=2; k++)
        if(room->nodes[j+k][i].robotVision != TILE_POTENTIAL_FIRE)
          pointFound = 0;

      if(pointFound) {
        for(int k=-2; k<=2; k++)
          room->nodes[j+k][i].robotVision = TILE_EMPTY;

        room->nodes[j][i].robotVision = TILE_INTERESTING;
      }
    }

  for(int i=1; i<room->sizeX-1; i++)
    for(int j=1; j<room->sizeY-1; j++) {
      int pointFound = 1;

      for(int k=-1; k<=1; k++)
        if(room->nodes[j+k][i].robotVision != TILE_POTENTIAL_FIRE)
          pointFound = 0;

      if(pointFound) {
        for(int k=-1; k<=1; k++)
          room->nodes[j+k][i].robotVision = TILE_EMPTY;

        room->nodes[j][i].robotVision = TILE_INTERESTING;
      }
    }

  for(int i=0; i<room->sizeX; i++)
    for(int j=0; j<room->sizeY; j++)
      if(room->nodes[j][i].robotVision == TILE_POTENTIAL_FIRE)
        room->nodes[j][i].robotVision = TILE_INTERESTING;
}
