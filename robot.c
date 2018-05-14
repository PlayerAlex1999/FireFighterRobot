#include "robot.h"
#include "room.h"

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

vector getPath(s_room* room, s_pos dest) {
  int pathFound = 0;
  s_node* last = 0;
  s_node* currentNode = &(room->nodes[room->robot.pos.y][room->robot.pos.x]);

  for(int i=0; i<room->sizeX; i++) {
    for(int j=0; j<room->sizeY; j++) {
      s_node* node = &(room->nodes[j][i]);
      node->H = sqrt(pow(fabs(dest.x - i)*1.0, 2) + pow(fabs(dest.y - j)*1.0, 2));
    }
  }

  vector openedList;
  vector closedList;

  vector_init(&openedList);
  vector_init(&closedList);
  vector_add(&openedList, currentNode);

  while(!pathFound) {
    int currentIdx=0;
    currentNode = (s_node*)vector_get(&openedList, 0);

    for(int i=1; i < vector_total(&openedList); i++) {
      if(currentNode->H < ((s_node*)vector_get(&openedList, i))->H) {
        currentNode = (s_node*)vector_get(&openedList, i);
        currentIdx = i;
      }
    }
    vector_add(&closedList, currentNode);
    vector_delete(&openedList, currentIdx);

    if(currentNode->pos.x == dest.x && currentNode->pos.y == dest.y) {
      pathFound = 1;
      last = currentNode;
      break;
    }

    for(int i=-1; i<=1; i++) {
      for(int j=-1; j<=1; j++) {
        if(currentNode->pos.y + i < 0 || currentNode->pos.y + i >= room->sizeY || currentNode->pos.x + j < 0 || currentNode->pos.x +j >= room->sizeX)
          continue;

        if(fabs(i) == fabs(j))
          continue;

        int status = mustBeIgnored(&openedList, &closedList, &(room->nodes[currentNode->pos.y + i][currentNode->pos.x + j]));
        if(status == -1) {
          room->nodes[currentNode->pos.y + i][currentNode->pos.x + j].parent = currentNode;
          room->nodes[currentNode->pos.y + i][currentNode->pos.x + j].G = currentNode->G+1;
          vector_add(&openedList, &(room->nodes[currentNode->pos.y + i][currentNode->pos.x + j]));
        } else if(status != -2) {
          s_node* node = (s_node*)vector_get(&openedList, status);
          if(node->G > currentNode->G + 1) {
            node->G = currentNode->G + 1;
            node->parent = currentNode;
            vector_set(&openedList, status, node);
          }
        }
      }
    }

    if(vector_total(&openedList) == 0)
      pathFound = 2;
  }

  vector path;
  vector_init(&path);
  while(last->parent != NULL) {
    vector_add(&path, last);
    last = last->parent;
  }

  return path;
}

int mustBeIgnored(vector* op, vector* cl, s_node* node) {
  for(int i=0; i<vector_total(cl); i++)
    if(vector_get(cl, i) == node)
      return -2;

  if(node->symb == TILE_WALL || node->symb == TILE_FIRE_LVL2 || node->symb == TILE_FIRE_LVL3)
    return -2;

  for(int i=0; i<vector_total(op); i++)
    if(vector_get(op, i) == node)
      return i;

  return -1;
}

int moveTo(s_room* room, vector* vect) {
  if(room->robot.pos.x == ((s_node*)vector_get(vect, 0))->pos.x && room->robot.pos.y == ((s_node*)vector_get(vect, 0))->pos.y)
    return 1;

  s_pos currentPos = room->robot.pos;
  s_pos nextPos;
  for(int i=1; i<vector_total(vect); i++) {
    if(room->robot.pos.x == ((s_node*)vector_get(vect, i))->pos.x && room->robot.pos.y == ((s_node*)vector_get(vect, i))->pos.y) {
      nextPos = ((s_node*)vector_get(vect, i-1))->pos;
      break;
    }
  }

  if(currentPos.y > nextPos.y)
    moveRobot(room, UP);
  else if(currentPos.x < nextPos.x)
    moveRobot(room, RIGHT);
  else if(currentPos.y > nextPos.y)
    moveRobot(room, DOWN);
  else if(currentPos.x > nextPos.x)
    moveRobot(room, LEFT);

  return 0;
}
