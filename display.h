#ifndef DISPLAY_H
#define DISPLAY_H

#include "includes.h"
#include "room.h"

#define WINDOW_X 1600
#define WINDOW_Y 900
#define MAX_PATH 128
#define GRAPHICS_MAP_TILESET "./data/graphics/map_tileset.png"
#define GRAPHICS_ROBOT_SPRITESHEET "./data/graphics/robot_spritesheet.png"
#define GRAPHICS_FIRE_ANIMATION "./data/graphics/fire_animation.png"

typedef struct s_SDLData {
    SDL_Surface* window;
    SDL_Surface* mapTileset;
    SDL_Surface* robotSpritesheet;
    SDL_Surface* fireAnimation;
} s_SDLData;

s_SDLData initSDL();
SDL_Rect getTileRect(char c);
void displayScreen(s_SDLData* data, s_room* room);

#endif
