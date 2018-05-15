#include "includes.h"
#include "room.h"

int main() {
  int stop=0;
  s_room room = loadRoom(DEFAULT_ROOM);
  vector path = getPath(&room, room.extinguisherPos);
  displayRoom(&room, 0);

  int idx = vector_total(&path)-1;

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

  vector_free(&path);
  return EXIT_SUCCESS;
}
