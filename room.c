#include "room.h"

s_room loadRoom(char* mapFilename) {
  s_room room;

  printf("Loading room : %s\n", mapFilename);
  FILE* file = fopen(mapFilename, "r+");

  if(!file) {
    printf("[CRITICAL] Can't load room %s\n", mapFilename);
    exit(EXIT_FAILURE);
  }

  fscanf(file, "%d:%d\n", &(room.sizeX), &(room.sizeY));
  printf("Room size : %dx%d\n", room.sizeX, room.sizeY);

  room.tiles = malloc(room.sizeY*sizeof(char*));
  for(int i=0; i<room.sizeY; i++)
    room.tiles[i] = malloc(room.sizeX*sizeof(char));

  int startPosFound=0, extinguisherPosFound=0, fireCenterFound=0;

  char c;
  for(int i=0; i<room.sizeY; i++) {
    for(int j=0; j<room.sizeX+1; j++) {
      c = fgetc(file);
      if(c == '\n')
        continue;

      if(c == TILE_START) {
        if(!startPosFound)
          room.startPos = (s_pos){j, i};
        else
          c = ' ';

        startPosFound++;
      }

      if(c == TILE_EXTINGUISHER) {
        if(!extinguisherPosFound)
          room.extinguisherPos = (s_pos){j, i};
        else
          c = ' ';

        extinguisherPosFound++;
      }

      if(c == TILE_FIRE_LVL3) {
        if(fireCenterFound)
          c = ' ';

        fireCenterFound++;
      }

      room.tiles[i][j] = c;
    }
  }

  if(startPosFound == 0) {
    printf("[CRITICAL] No starting position found.\n");
    exit(EXIT_FAILURE);
  } else if (startPosFound > 1) {
    printf("[WARNING] More than one starting position found. Copies have been deleted.\n");
  }

  if(extinguisherPosFound == 0) {
    printf("[CRITICAL] No extinguisher found\n");
    exit(EXIT_FAILURE);
  } else if (extinguisherPosFound > 1) {
    printf("[WARNING] More than one extinguisher found. Copies have been deleted\n");
  }

  if(fireCenterFound== 0) {
    printf("[CRITICAL] No fire center found\n");
    exit(EXIT_FAILURE);
  } else if (fireCenterFound > 1) {
    printf("[WARNING] More than one fire center found. Copies have been deleted\n");
  }

  printf("Starting position : (%d;%d)\n", room.startPos.x, room.startPos.y);
  printf("Extinguisher : (%d;%d)\n", room.extinguisherPos.x, room.extinguisherPos.y);
  printf("\n");

  room.robot = initRobot(room.startPos.x, room.startPos.y);
  return room;
}

void displayRoom(s_room* room) {
  for(int i=0; i<10; i++)
    printf("\n");

  for(int i=0; i<room->sizeY; i++) {
    for(int j=0; j<room->sizeX; j++)
      if(isAtPos(&(room->robot), j, i))
        printf("%c", displayRobot(&(room->robot)));
      else
        printf("%c", room->tiles[i][j]);

    printf("\n");
  }
}
