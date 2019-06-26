#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include "graphics.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
/**
 * @brief Contains the user's current points and the highest number.
 */
 typedef struct{
   int user_points; /**< User's current points. */
   int highest_points; /**< The highest points number gained. */
 }points;
 /**
  * @brief Contains the computer coordinates.
  */
typedef struct{
  int xc; /**< The X coordinate. */
  int yc; /**< The Y coordinate. */
}computerEnteries;
/**
 * @brief Contains all the images needed to render the pick screen.
 */
typedef struct {
   SDL_Surface * backPicker; /**< The background. */
   SDL_Rect backPos; /**< The position of background. */
   SDL_Surface * backbut; /**< image of back button. */
   SDL_Surface * backbut2; /**< mouse hover image of back button. */
   SDL_Rect  backbutPos; /**< back button position. */
   char pick; /**< Indicates what the user chose it can be X or O.*/
}picker;
/**
 * @brief a struct contains one single line and its position.
 */
struct lines{
  SDL_Surface * line; /**< Line image. */
  SDL_Rect linePos; /**< Line image position. */
};
/**
 * @brief Contains all the data of the game play screen.
 */
typedef struct{
  SDL_Surface * back; /**< the main background. */
  SDL_Rect backPos;  /**< the main background position. */
  SDL_Surface * x;  /**< the X image */
  SDL_Surface * o; /**< the O image. */
  SDL_Rect input;  /**< position of X and O (this position varies depending on the input). */
  SDL_Surface * backbut;  /**< image of back button */
  SDL_Rect backbutPos;  /**< position of back button. */
  SDL_Rect scorePos;  /**< score postion on screen */
  SDL_Surface * backScore;  /**< background of the score */
  SDL_Rect backScorePos;  /**< position of back of the score */
  SDL_Surface * splashCharIndicatorX; /**< Splash screen of You are playing with X */
    SDL_Surface * splashCharIndicatorO; /**< Splash screen of You are playing with O */
  SDL_Rect splashIndicatorPos; /**< Splash screen of indicator Position */
  struct lines l[8];
}playgameScreen;
int initPickScreen(picker *p);
picker getPick (SDL_Surface * screen, SDL_Event event, picker p, soundFX sfx, control c);
void init (char (*m)[3]);
void computerBrain(char (*m)[3], int *xc, int *yc, int (*t)[3], int (*ta)[3], char whatComputerChose);
void initDeffTable(int (*t)[3]);
void initAttTable(int (*ta)[3]);
playgameScreen initGamePlay();
int player(char (*m)[3],SDL_Surface *screen, playgameScreen pgs, char c, SDL_Event event, soundFX sfx , control con);
void showGamePlay(playgameScreen pgs,SDL_Surface *screen);
void printOnTable(computerEnteries ce, char (*m)[3], SDL_Surface * screen, playgameScreen pgs, char c);
int checkfin(char (*m)[3]);
void checkwin(char (*m)[3], int *winner,char whatComputerChose, int *won,SDL_Surface * screen, playgameScreen pgs);
void manageScore (int winner , int *splayer1, int *splayer2);
void showScore(int winner, int scomputer, int splayer,SDL_Surface * screen, playgameScreen pgs, int whichMode);
void printPoints (points p, SDL_Surface * screen);
void managePoints(points *p, int winner, int scomputer, int splayer, SDL_Surface *screen);
int fileManipulation(int flag, int points);
#endif
