#include "includes.h"
#include "room.h"

int main() {
  int stop = 0;

  srand(time(NULL));

  s_SDLData SDLData = initSDL();

  s_room room = loadRoom(DEFAULT_ROOM);
  vector path = getBestPath(&room, room.startPos, room.extinguisherPos);
  vector firePossibilies;
  int possibilityTested = 0;
  int possibilityGet = 0;
  float timeBeforeExit = 0;

  displayRoom(&room, 0);
  displayScreen(&SDLData, &room);

  int idx = vector_total(&path)-2;

  //printf("%d;%d\n", room.extinguisherPos.x, room.extinguisherPos.y);
  //printf("%d;%d\n", ((s_node*)vector_get(&path,0))->pos.x, ((s_node*)vector_get(&path,0))->pos.y);
  //usleep(10000000);

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
        else {
          if(room.robot.hasExtinguisher && room.robot.pos.x == room.robot.lastFire.x && room.robot.pos.y == room.robot.lastFire.y) {
            room.robot.status = STATUS_EXTINGUISH_FIRE;
            if(room.nodes[room.robot.pos.y][room.robot.pos.x].symb == TILE_FIRE_LVL1)
              room.nodes[room.robot.pos.y][room.robot.pos.x].robotVision = TILE_FIRE_LVL1;
          } else {
            printf("[WARNING] Unpredicted behavior\n");
            exit(1);
          }
        }
      } else if(room.robot.status == STATUS_GO_TO_FIRE) {
        vector_free(&path);
        path = getBestPath(&room, room.robot.pos, room.robot.lastFire);

        idx = vector_total(&path) - 2;
        room.robot.status = STATUS_SEARCH_FIRE;
      } else if (room.robot.status == STATUS_EXTINGUISH_FIRE) {
        if(!possibilityGet) {
          vector_free(&path);
          firePossibilies = fireCenterPosiblePosition(&room);
          possibilityTested = 0;
          possibilityGet = 1;

          if(vector_total(&firePossibilies) == 0) {
            printf("[CRITICAL] Can't find fire\n");
            exit(EXIT_FAILURE);
          }

          path = getBestPath(&room, room.robot.pos, ((s_node*)vector_get(&firePossibilies, possibilityTested))->pos);
          idx = vector_total(&path)-2;
        }
        if(idx >= 0)
          idx = moveTo(&room, &path, idx);
        else if (possibilityTested+1 < vector_total(&firePossibilies)) {
          possibilityTested++;
          int ok=0;
          while(!ok && possibilityTested+1 < vector_total(&firePossibilies)) {
            if(room.nodes[((s_node*)vector_get(&firePossibilies, possibilityTested))->pos.y][((s_node*)vector_get(&firePossibilies, possibilityTested))->pos.x].robotVision == TILE_VISITED)
              possibilityTested++;
            else
              ok=1;
          }
          path = getBestPath(&room, room.robot.pos, ((s_node*)vector_get(&firePossibilies, possibilityTested))->pos);
          idx = vector_total(&path)-2;
        } else if (room.robot.status != STATUS_WAIT_TO_EXIT){
          printf("[CRITICAL] Fire not found\n");
          stop=1;
        }
      } else if (room.robot.status == STATUS_WAIT_TO_EXIT) {
        if(timeBeforeExit < 1) {
          for(int i=0; i<room.sizeX; i++)
            for(int j=0; j<room.sizeY; j++)
              if(room.nodes[j][i].symb == TILE_FIRE_LVL1 || room.nodes[j][i].symb == TILE_FIRE_LVL2 || room.nodes[j][i].symb == TILE_FIRE_LVL3)
                room.nodes[j][i].symb = TILE_EXTINGUISHED_FIRE;
        }

        timeBeforeExit += 0.1;
        if(timeBeforeExit > 10)
          stop=1;

        printf("The programm will close in few seconds\n");
      }
      else {
        stop = 1;
      }

      if(SDL_PollEvent(&event)) {
        stop = getEvents(&event);
      }

      SDL_Delay(100);
  }

  displayRoom(&room, 1);
  vector_free(&path);
  freeSDL(&SDLData);

  return EXIT_SUCCESS;
}
