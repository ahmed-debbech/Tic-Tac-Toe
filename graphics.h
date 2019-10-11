#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
/**
 * @brief Contains the images and their positions for the main official menu at the begginig.
 */
typedef struct{
  SDL_Surface * splash; /**< Splash image. */
  SDL_Surface * menuBack; /**< menu background image. */
  SDL_Surface * playbut; /**< play button image. */
  SDL_Surface * playbut2; /**< play button image hovered. */
  SDL_Surface * helpbut; /**< help button image . */
  SDL_Surface * helpbut2; /**< help button image hovered. */
  SDL_Surface * aboutbut; /**< about button image . */
  SDL_Surface * aboutbut2; /**< about button image hovered. */
  SDL_Surface * storebut; /**< store button image . */
  SDL_Surface * storebut2; /**< store button image hovered. */
  SDL_Surface * soundbut; /**< sound button image. */
  SDL_Surface * soundbut2; /**< sound button image muted. */
  SDL_Surface * powerbut; /**< power button image. */
  //positions
  SDL_Rect  splashPos; /**< splash position. */
  SDL_Rect menuBackPos; /**< menu beckground position. */
  SDL_Rect playbutPos; /**< play button position. */
    SDL_Rect storebutPos; /**< store button position. */
  SDL_Rect helpbutPos; /**< help button position. */
  SDL_Rect aboutbutPos; /**< about button position. */
  SDL_Rect soundbutPos; /**< sound button position. */
  SDL_Rect powerbutPos; /**< power button position. */
}menu;
/**
*@brief Contains images and positions of the help screen after button help is pressed.
*/
typedef struct{
  SDL_Surface * backhelp; /**< help button image . */
  //positions
  SDL_Rect backPos; /**< help button position. */
}help;
/**
*@brief Contains images and positions of the about screen after button help is pressed.
*/
typedef struct{
  SDL_Surface * backabout; /**< about button image . */
  //positions
  SDL_Rect backPos; /**< about button position. */
}about;
/**
*@brief Contains images and positions of the common buttons
*/
typedef struct{
  SDL_Surface * backbut;  /**< back button image. */
  SDL_Surface * backbut2; /**< back button image hovered. */
  //positions
  SDL_Rect  backbutPos; /**< back button position. */
}buttons;

/**
*@brief Contains all the sounds necessary to run the game.
*/
typedef struct{
  Mix_Chunk * butHover; /**< the hover sound clip */
   Mix_Chunk * butClick; /**< the click sound clip. */
   Mix_Chunk * lose; /**< lose sound clip. */
   Mix_Chunk * winning; /**< winning sound clip. */
   Mix_Chunk * tap; /**< tap sound clip. */
   int soundMuted; /**< a flag indicates if the sound is muted or not. */
}soundFX;
/**
*@brief Contains images and positions of the menu after play button is clicked.
*/
typedef struct {
  SDL_Surface * computer; /**< computer button image. */
  SDL_Surface * computer2; /**< computer button image hovered. */
  SDL_Surface * friend; /**< friend button image. */
  SDL_Surface * friend2; /**< friend button image hovered. */
  SDL_Surface * levels; /**< levels button image. */
  SDL_Surface * levels2; /**< levels button image hovered. */
  SDL_Surface * back; /**< background image of the menu. */
  //positions
  SDL_Rect  computerPos; /**< computer button position. */
  SDL_Rect friendPos; /**< friend button position. */
  SDL_Rect levelsPos; /**< levels button position. */
  SDL_Rect backPos; /**< background image position. */
}menuPlayGame;
/**
*@brief Contains images and positions of the levels package screen after levels button is clicked.
*/
typedef struct{
  SDL_Surface * levelsBack; /**< background of levels screen. */
  SDL_Surface * pack1; /**< pack 1 button image. */
  SDL_Surface * pack2; /**< pack 2 button image. */
  SDL_Surface * pack3; /**< pack 3 button image. */
  SDL_Surface * pack1_hover; /**< pack 1 button image hovered. */
  SDL_Surface * pack2_hover; /**< pack 2 button image hovered.*/
  SDL_Surface * pack3_hover; /**< pack 3 button image hovered. */
  SDL_Rect levelsBackPos; /**< position of background */
  SDL_Rect pack1Pos; /**< position of pack1 image position */
  SDL_Rect pack2Pos; /**< position of pack2 image position */
  SDL_Rect pack3Pos; /**< position of pack3 image position */
  short packChosen; /**< the number of pack chosen bu the user. */
}levelsPacks;
//prototypes
buttons initButtons();
menu initOffMenu();
soundFX initSounds();
void showOffMenu(menu mc, SDL_Surface * screen, soundFX sfx);
int menuMotion(menu mc, SDL_Surface * screen,
   SDL_Event event, soundFX sfx);
int menuClicks (menu mc, SDL_Surface * screen,
  SDL_Event event , soundFX *sfx);
help initHelp();
void showHelp(help h, SDL_Surface* screen, buttons bu);
int helpMotion(buttons bu,help h,
  SDL_Surface * screen, SDL_Event event);
int helpClicks(SDL_Event event, buttons bu, soundFX sfx);
about initAbout();
void showAbout(about a, SDL_Surface* screen, buttons bu);
int aboutMotion(buttons bu,about a,
SDL_Surface * screen, SDL_Event event);
int aboutClicks(SDL_Event event, buttons bu, soundFX sfx);
menuPlayGame initMenuPlay();
void showMenuPlay(menuPlayGame mpg, SDL_Surface *screen, buttons bu);
int menuPlayMotion(buttons bu, menuPlayGame mpg, SDL_Surface * screen, SDL_Event event, soundFX sfx);
int menuPlayClicks(SDL_Event event, buttons bu, menuPlayGame mpg, soundFX sfx);
levelsPacks initLevelsMenu();
void showLevelsMenu(levelsPacks lp, SDL_Surface * screen, buttons bu);
void levelsMenuMotion(buttons bu, levelsPacks lp, SDL_Surface * screen, SDL_Event event, soundFX sfx);
levelsPacks getPackChoice(levelsPacks lp, buttons bu, soundFX sfx, SDL_Surface * screen);
void printLevelsNumber(int levels, int num, SDL_Surface * screen);
#endif
