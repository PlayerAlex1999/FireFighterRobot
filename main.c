#include "includes.h"
#include "room.h"

int main() {
  int stop=0;
  s_room room = loadRoom(DEFAULT_ROOM);
  vector path = getPath(&room, room.extinguisherPos);
  displayRoom(&room);

  while(!stop) {
      displayRoom(&room);
      stop = moveTo(&room, &path);
      usleep(100000);
  }

  return EXIT_SUCCESS;
}
