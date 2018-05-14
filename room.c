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

  char c;
  for(int i=0; i<room.sizeY; i++) {
    for(int j=0; j<room.sizeX+1; j++) {
      c = fgetc(file);
      if(c == '\n')
        continue;

      room.tiles[i][j] = c;
    }
  }

  displayRoom(room);
  return room;
}

void displayRoom(s_room room) {
  for(int i=0; i<room.sizeY; i++) {
    for(int j=0; j<room.sizeX; j++)
      printf("%c", room.tiles[i][j]);

    printf("\n");
  }
}
