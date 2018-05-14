#include "includes.h"
#include "room.h"

int main() {
  int stop=0;
  s_room room = loadRoom(DEFAULT_ROOM);
  vector path = getPath(&room, room.extinguisherPos);
  displayRoom(&room, 0);

  while(!stop) {
      displayRoom(&room, 1);
      stop = moveTo(&room, &path);
      usleep(100000);
  }

  return EXIT_SUCCESS;
}
