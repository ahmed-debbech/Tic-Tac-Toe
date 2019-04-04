#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"

typedef struct{
  SDL_Surface * splash;
  SDL_Surface * menuBack;
  SDL_Surface * playbut;
  SDL_Surface * playbut2;
  SDL_Surface * helpbut;
  SDL_Surface * helpbut2;
  SDL_Surface * aboutbut;
  SDL_Surface * aboutbut2;
  SDL_Surface * soundbut;
  SDL_Surface * soundbut2;
  SDL_Surface * powerbut;
  //positions
  SDL_Rect  splashPos;
  SDL_Rect menuBackPos;
  SDL_Rect playbutPos;
  SDL_Rect helpbutPos;
  SDL_Rect aboutbutPos;
  SDL_Rect soundbutPos;
  SDL_Rect powerbutPos;
}menu;
typedef struct {
   int soundMuted;
}control;
typedef struct{
  Mix_Chunk * butHover;
   Mix_Chunk * butClick;
}soundFX;
menu initOffMenu();
soundFX initSounds();
void showOffMenu(menu mc, SDL_Surface * screen);
int menuMotion(menu mc, SDL_Surface * screen, SDL_Event event, control c, soundFX sfx);
int menuClicks (menu mc, SDL_Surface * screen, SDL_Event event ,control c, soundFX *sfx);
#endif
