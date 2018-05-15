#include "includes.h"
#include "room.h"

int main() {
  int stop=0;
  s_room room = loadRoom(DEFAULT_ROOM);
  vector path = getBestPath(&room, room.startPos, room.extinguisherPos);
  displayRoom(&room, 0);

  int idx = vector_total(&path)-2;

  while(!stop) {
      displayRoom(&room, 1);

      if(idx != -1)
        idx = moveTo(&room, &path, idx);
      else
        stop = 1;

      usleep(50000);
  }
  setEmptyTilesInteresting(&room);
  displayRoom(&room, 1);

  printf("%d\n", getDistance(&room, (s_pos){6, 7}));

  vector_free(&path);
  return EXIT_SUCCESS;
}
