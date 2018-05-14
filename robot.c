#include "robot.h"

s_robot initRobot(int x, int y) {
  s_robot robot;
  robot.pos = (s_pos){x, y};
  robot.firePosition = (s_pos){-1, -1};
  robot.hasExtinguisher = 0;

  robot.healthPoints = DEFAULT_HP;

  return robot;
}

void goToAdjacentTile(s_robot* robot, e_direction dir) {
  switch (dir) {
    case UP:
      robot->pos.y--;
      break;

    case RIGHT:
      robot->pos.x++;
      break;

    case DOWN:
      robot->pos.y++;
      break;

    case LEFT:
      robot->pos.x--;
      break;

    default:
      printf("[WARNING] Uknown direction : %d\n", dir);
  }
}

char displayRobot(s_robot* robot) {
  if(robot->hasExtinguisher == 1)
    return TILE_ROBOT;

  return TILE_ROBOT_WITH_EXTINGUISHER;
}

int isAtPos(s_robot* robot, int x, int y) {
  if(robot->pos.x == x && robot->pos.y == y) {
    return 1;
  }

  return 0;
}