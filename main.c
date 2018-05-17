#include "includes.h"
#include "room.h"

int main() {
  int stop = 0;

  srand(time(NULL));

  s_SDLData SDLData = initSDL();

  s_room room = loadRoom(DEFAULT_ROOM);
  vector path = getBestPath(&room, room.startPos, room.extinguisherPos);
  displayRoom(&room, 0);
  displayScreen(&SDLData, &room);

  int idx = vector_total(&path)-2;

  while(!stop) {
      SDL_Event event;
      displayRoom(&room, 1);
      displayScreen(&SDLData, &room);

      if(room.robot.status == STATUS_GO_TO_EXTINGUISHER) {
        if(idx >= 0)
          idx = moveTo(&room, &path, idx);
        else
          printf("[WARNING] Unpredicted behavior\n");
      }
      else if(room.robot.status == STATUS_DETERMINE_INTERESTING_POINT) {
        vector_free(&path);
        path = nextNodePath(&room);

        idx = vector_total(&path)-2;
        printf("%d\n", idx);
      }
      else if(room.robot.status == STATUS_SEARCH_FIRE) {
        if(idx >= 0)
          idx = moveTo(&room, &path, idx);
        else
          printf("[WARNING] Unpredicted behavior\n");
      } else if(room.robot.status == STATUS_GO_TO_FIRE) {
        vector_free(&path);
        for(int i=0; i < room.sizeX; i++)
          for(int j=0; j < room.sizeY; j++)
            if(room.nodes[j][i].robotVision == TILE_FIRE_LVL1 || room.nodes[j][i].robotVision == TILE_FIRE_LVL2 || room.nodes[j][i].robotVision == TILE_FIRE_LVL3) {
              path = getBestPath(&room, room.robot.pos, (s_pos){i, j});
              break;
            }

        idx = vector_total(&path) - 2;
      } else {
        stop = 1;
      }

      if(SDL_PollEvent(&event)) {
        stop = getEvents(&event);
      }

      SDL_Delay(100);
  }
  displayRoom(&room, 1);

  //PAS OUBLIER DE FREE

  vector_free(&path);

  SDL_Quit();
  return EXIT_SUCCESS;
}
