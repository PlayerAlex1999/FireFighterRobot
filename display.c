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
  data.robotSpritesheet = IMG_Load(GRAPHICS_ROBOT_SPRITESHEET);
  data.fireAnimation = IMG_Load(GRAPHICS_FIRE_ANIMATION);

  return data;
}

SDL_Rect getTileRect(char c) {
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
      tileRect.x = 64;
      tileRect.y = 0;
      break;

    case TILE_FIRE_LVL2:
      tileRect.x = 64;
      tileRect.y = 0;
      break;

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
        SDL_Rect src = getTileRect(room->nodes[j][i].symb);
        SDL_Rect dest;
        dest.x = i*32;
        dest.y = j*32;
        SDL_BlitSurface(data->mapTileset, &src, data->window, &dest);
      }
  } else {
    for(int i=-14; i<=11; i++)
      for(int j=-12; j<=12; j++) {
        SDL_Rect src;
        SDL_Rect dest;
        dest.x = 11.5*32+j*32;
        dest.y = 13.5*32+i*32;
        if(room->robot.pos.x + j < 0 || room->robot.pos.y + i < 0 || room->robot.pos.x + j >= room->sizeX || room->robot.pos.y + i >= room->sizeY)
          src = getTileRect(TILE_BLACK);
        else
          src = getTileRect(room->nodes[room->robot.pos.y + i][room->robot.pos.x + j].symb);

        SDL_BlitSurface(data->mapTileset, &src, data->window, &dest);
      }
  }

  SDL_Flip(data->window);
}
