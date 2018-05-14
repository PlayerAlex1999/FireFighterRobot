#include "robot.h"

s_robot initRobot(int x, int y) {
  s_robot robot;
  robot.pos = (s_pos){x, y};
  robot.firePosition = (s_pos){-1, -1};
  robot.hasExtinguisher = 0;

  robot.healthPoints = DEFAULT_HP;

  return robot;
}

char displayRobot(s_robot* robot) {
  if(robot->hasExtinguisher == 1)
    return TILE_ROBOT_WITH_EXTINGUISHER;

  return TILE_ROBOT;
}

int isAtPos(s_robot* robot, int x, int y) {
  if(robot->pos.x == x && robot->pos.y == y) {
    return 1;
  }

  return 0;
}

s_node* getPath(s_room* room, s_pos dest) {
  int pathFound = 0;
  s_node* currentNode = &(room->nodes[room->robot.pos.y][room->robot.pos.x]);

  for(int i=0; i<room->sizeX; i++) {
    for(int j=0; j<room->sizeY; j++) {
      s_node* node = &(room->nodes[j][i]);
      node->H = sqrt(pow(fabs(dest.x - i)*1.0, 2) + pow(fabs(dest.y - j)*1.0, 2));
    }
  }

  return NULL;
  vector openedList;
  vector closedList;

  vector_init(&openedList);
  vector_init(&closedList);
  vector_add(&openedList, currentNode);

  while(!pathFound) {
    currentNode = (s_node*)vector_get(&openedList, 0);
    for(int i=1; i < vector_total(&openedList); i++) {
      if(currentNode->H < ((s_node*)vector_get(&openedList, i))->H)
        currentNode = (s_node*)vector_get(&openedList, i);
    }

    for(int i=-1; i<=1; i++) {
      for(int j=-1; j<=1; j++) {
        if(currentNode->pos.y + i < 0 || currentNode->pos.y + i >= sizeY || currentNode->pos.x + j < 0 || currentNode->pos.x +j >= sizeX)
          continue;

        if(!mustBeIgnored(&closedList, &(room->nodes[currentNode->pos.y + i][currentNode->pos.x + j])))
          vector_add(&openedList, &(room->nodes[currentNode->pos.y + i][currentNode->pos.x + j]));
      }
    }

    if(vector_total(&openedList) == 0)
      pathFound = 2;
  }

  return NULL;
}

int mustBeIgnored(vector* vect, s_node* node) {
  for(int i=0; i<vector_total(vect); i++)
    if(vector_get(vect, i) == node)
      return 1;

  if(node->symb == TILE_WALL || node->symb == TILE_FIRE_LVL2 || node->symb == TILE_FIRE_LVL3)
    return 1;

  return 0;
}
