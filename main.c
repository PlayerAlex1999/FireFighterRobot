#include "includes.h"
#include "room.h"

int main() {
  int stop=0;
  s_room room = loadRoom(DEFAULT_ROOM);

  while(!stop) {
      displayRoom(&room);
      usleep(500000);
  }

  return EXIT_SUCCESS;
}
