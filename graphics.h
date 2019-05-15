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
  SDL_Surface * computer;
  SDL_Surface * computer2;
  SDL_Surface * friend;
  SDL_Surface * friend2;
  SDL_Surface * back;
  //positions
  SDL_Rect  computerPos;
  SDL_Rect friendPos;
  SDL_Rect backPos;
}menuOfPlay;
typedef struct{
  SDL_Surface * backhelp;
  //positions
  SDL_Rect backPos;
}help;
typedef struct{
  SDL_Surface * backabout;
  //positions
  SDL_Rect backPos;
}about;
typedef struct{
  SDL_Surface * backbut;
  SDL_Surface * backbut2;
  //positions
  SDL_Rect  backbutPos;
}buttons;
typedef struct {
   int soundMuted;
}control;
typedef struct{
  Mix_Chunk * butHover;
   Mix_Chunk * butClick;
}soundFX;
typedef struct {
  SDL_Surface * back;
   SDL_Surface * computer;
   SDL_Surface * friend;
   SDL_Surface * computer2;
   SDL_Surface * friend2;
   SDL_Rect computerPos;
   SDL_Rect friendPos;
   SDL_Rect backPos;
}menuPlayGame;
buttons initButtons();
menu initOffMenu();
soundFX initSounds();
void showOffMenu(menu mc, SDL_Surface * screen, control c);
int menuMotion(menu mc, SDL_Surface * screen,
   SDL_Event event, control c, soundFX sfx);
int menuClicks (menu mc, SDL_Surface * screen,
  SDL_Event event ,control * c, soundFX *sfx);
help initHelp();
void showHelp(help h, SDL_Surface* screen, buttons bu);
int helpMotion(buttons bu,help h,
  SDL_Surface * screen, SDL_Event event);
int helpClicks(SDL_Event event, buttons bu);
about initAbout();
void showAbout(about a, SDL_Surface* screen, buttons bu);
int aboutMotion(buttons bu,about a,
  SDL_Surface * screen, SDL_Event event);
int aboutClicks(SDL_Event event, buttons bu);
menuPlayGame initMenuPlay();
void showMenuPlay(menuPlayGame mpg, SDL_Surface *screen, buttons bu);
int menuPlayMotion(buttons bu, menuPlayGame mpg, SDL_Surface * screen, SDL_Event event,control c, soundFX sfx);
int menuPlayClicks(SDL_Event event, buttons bu, menuPlayGame mpg, control c, soundFX sfx);
#endif
