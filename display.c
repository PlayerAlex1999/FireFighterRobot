#include "display.h"

s_SDLData initSDL() {
  s_SDLData data;

  if(SDL_Init(SDL_INIT_VIDEO) == -1) {
    printf("[CRITICAL] Error while loading SDL : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  data.window = NULL;
  data.window = SDL_SetVideoMode(WINDOW_X, WINDOW_Y, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if(!data.window) {
    printf("[CRITICAL] Error while creating the window : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_WM_SetCaption("Firefighter robot - Projet de fin d'année CIR 1 ISEN Yncrea Rennes | Alexandre THOMAS", NULL);

  data.mapTileset = IMG_Load(GRAPHICS_MAP_TILESET);
  data.robotVisionTileset = NULL;
  data.robotVisionTileset = IMG_Load(GRAPHICS_ROBOT_VISION_TILESET);
  if(!data.robotVisionTileset)
    usleep(1000000000);
  data.robotSpritesheet = IMG_Load(GRAPHICS_ROBOT_SPRITESHEET);
  data.fireAnimation = IMG_Load(GRAPHICS_FIRE_ANIMATION);
  data.fireAnimationStep = -2;

  return data;
}

SDL_Rect getRobotSprite(s_robot* robot) {
  SDL_Rect robotSprite;
  robotSprite.w = 32;
  robotSprite.h = 32;
  robotSprite.y = 32*robot->direction;

  if(!robot->hasExtinguisher)
    robotSprite.x = 0;
  else if(robot->status != STATUS_EXTINGUISH_FIRE)
    robotSprite.x = 32;
  else
    robotSprite.x = 64;

  return robotSprite;
}

SDL_Rect getMapTileRect(char c) {
  SDL_Rect tileRect;
  tileRect.w = 32;
  tileRect.h = 32;

  switch (c) {
    case TILE_EMPTY:
      tileRect.x = 0;
      tileRect.y = 0;
      break;

    case TILE_EXTINGUISHED_FIRE:
      tileRect.x = 32;
      tileRect.y = 0;
      break;

    case TILE_FIRE_LVL1:
    case TILE_FIRE_LVL2:
    case TILE_FIRE_LVL3:
      tileRect.x = 64;
      tileRect.y = 0;
      break;

    case TILE_WALL:
      tileRect.x = 0;
      tileRect.y = 32;
      break;

    case TILE_BLACK:
      tileRect.x = 32;
      tileRect.y = 32;
      break;

    case TILE_EXTINGUISHER:
      tileRect.x = 64;
      tileRect.y = 32;
      break;

    default:
      tileRect.x=0;
      tileRect.y=0;
  }

  return tileRect;
}

SDL_Rect getRobotVisionTileRect(char c) {
  SDL_Rect tileRect;
  tileRect.w = 32;
  tileRect.h = 32;

  switch (c) {
    case TILE_EMPTY:
    case TILE_EXTINGUISHED_FIRE:
      tileRect.x = 0;
      tileRect.y = 0;
      break;

    case TILE_FIRE_LVL1:
      tileRect.x = 32;
      tileRect.y = 0;
      break;

    case TILE_FIRE_LVL2:
      tileRect.x = 64;
      tileRect.y = 0;
      break;

    case TILE_FIRE_LVL3:
      tileRect.x = 96;
      tileRect.y = 0;
      break;

    case TILE_WALL:
    case TILE_BLACK:
      tileRect.x = 96;
      tileRect.y = 32;
      break;

    case TILE_START:
      tileRect.x = 0;
      tileRect.y = 32;
      break;

    case TILE_VISITED:
    case TILE_NOFIRE:
      tileRect.x = 64;
      tileRect.y = 32;
      break;

    case TILE_EXTINGUISHER:
    case TILE_INTERESTING:
      tileRect.x = 32;
      tileRect.y = 32;
      break;

    default:
      tileRect.x=0;
      tileRect.y=0;
  }

  return tileRect;
}

SDL_Rect getFireAnimationStep(char c, s_SDLData* data) {
  SDL_Rect fireRect;
  fireRect.w = 32;
  fireRect.h = 32;
  fireRect.x = 32*fabs(data->fireAnimationStep);

  switch(c) {
    case TILE_FIRE_LVL1:
      fireRect.y = 0;
      break;

    case TILE_FIRE_LVL2:
      fireRect.y = 32;
      break;

    case TILE_FIRE_LVL3:
      fireRect.y = 64;
      break;

    default:
      fireRect.y = 0;
  }

  data->fireAnimationStep++;
  if(data->fireAnimationStep > 2)
    data->fireAnimationStep = -2;

  return fireRect;
}

void displayScreen(s_SDLData* data, s_room* room) {
  SDL_FillRect(data->window, NULL, SDL_MapRGB(data->window->format, 0, 0, 0));

  SDL_Rect banner;
  banner.x=0;
  banner.y=818;
  banner.w=1600;
  banner.h=84;
  SDL_FillRect(data->window, &banner, SDL_MapRGB(data->window->format, 200, 200, 200));

  if(room->sizeX < WINDOW_X/(32*2) && room->sizeY < WINDOW_Y) {
    for(int i=0; i < room->sizeX; i++)
      for(int j=0; j < room->sizeY; j++) {
        SDL_Rect srcMap = getMapTileRect(room->nodes[j][i].symb);
        SDL_Rect srcRobotVision = getRobotVisionTileRect(room->nodes[j][i].robotVision);
        SDL_Rect destMap;
        destMap.x = i*32;
        destMap.y = j*32;
        SDL_Rect destRobotVision;
        destRobotVision.x = WINDOW_X/2 + i*32;
        destRobotVision.y = j*32;

        SDL_BlitSurface(data->mapTileset, &srcMap, data->window, &destMap);
        SDL_BlitSurface(data->robotVisionTileset, &srcRobotVision, data->window, &destRobotVision);
      }

    SDL_Rect robotSprite = getRobotSprite(&(room->robot));
    SDL_Rect destMap;
    destMap.x = room->robot.pos.x*32;
    destMap.y = room->robot.pos.y*32;
    SDL_Rect destRobotVision;
    destRobotVision.x = WINDOW_X/2 + room->robot.pos.x*32;
    destRobotVision.y = room->robot.pos.y*32;

    SDL_BlitSurface(data->robotSpritesheet, &robotSprite, data->window, &destMap);
    SDL_BlitSurface(data->robotSpritesheet, &robotSprite, data->window, &destRobotVision);

  } else {
    for(int i=-14; i<=11; i++)
      for(int j=-12; j<=12; j++) {
        SDL_Rect srcMap;
        SDL_Rect destMap;
        destMap.x = 11.5*32+j*32;
        destMap.y = 13.5*32+i*32;
        if(room->robot.pos.x + j < 0 || room->robot.pos.y + i < 0 || room->robot.pos.x + j >= room->sizeX || room->robot.pos.y + i >= room->sizeY)
          srcMap = getMapTileRect(TILE_BLACK);
        else
          srcMap = getMapTileRect(room->nodes[room->robot.pos.y + i][room->robot.pos.x + j].symb);

        SDL_Rect srcRobotVision;
        SDL_Rect destRobotVision;
        destRobotVision.x = 38.5*32+j*32;
        destRobotVision.y = 13.5*32+i*32;
        if(room->robot.pos.x + j < 0 || room->robot.pos.y + i < 0 || room->robot.pos.x + j >= room->sizeX || room->robot.pos.y + i >= room->sizeY)
          srcRobotVision = getRobotVisionTileRect(TILE_BLACK);
        else
          srcRobotVision = getRobotVisionTileRect(room->nodes[room->robot.pos.y + i][room->robot.pos.x + j].robotVision);

        SDL_BlitSurface(data->mapTileset, &srcMap, data->window, &destMap);
        SDL_BlitSurface(data->robotVisionTileset, &srcRobotVision, data->window, &destRobotVision);

        if(room->robot.pos.x + j >= 0 && room->robot.pos.y + i >= 0 && room->robot.pos.x + j < room->sizeX && room->robot.pos.y + i < room->sizeY)
          if(room->nodes[room->robot.pos.y + i][room->robot.pos.x + j].symb == TILE_FIRE_LVL1
            || room->nodes[room->robot.pos.y + i][room->robot.pos.x + j].symb == TILE_FIRE_LVL2
            || room->nodes[room->robot.pos.y + i][room->robot.pos.x + j].symb == TILE_FIRE_LVL3) {

              SDL_Rect srcFire = getFireAnimationStep(room->nodes[room->robot.pos.y + i][room->robot.pos.x + j].symb, data);
              SDL_BlitSurface(data->fireAnimation, &srcFire, data->window, &destMap);
            }
      }

    SDL_Rect robotSprite = getRobotSprite(&(room->robot));
    SDL_Rect destMap;
    destMap.x = 11.5*32;
    destMap.y = 13.5*32;
    SDL_Rect destRobotVision;
    destRobotVision.x = 38.5*32;
    destRobotVision.y = 13.5*32;

    SDL_BlitSurface(data->robotSpritesheet, &robotSprite, data->window, &destMap);
    SDL_BlitSurface(data->robotSpritesheet, &robotSprite, data->window, &destRobotVision);
  }

  SDL_Flip(data->window);
}

int getEvents(SDL_Event* event) {
  printf("%d\n", event->type);
  printf("%d\n", SDL_QUIT);
  switch (event->type) {
    case SDL_QUIT:
      return 1;
      break;

    default:
      return 0;
  }

  return 0;
}
