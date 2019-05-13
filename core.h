#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
typedef struct{
  int xc;
  int yc;
}computerEnteries;

typedef struct {
   SDL_Surface * backPicker;
   SDL_Rect backPos;
   SDL_Surface * backbut;
   SDL_Surface * backbut2;
   SDL_Rect  backbutPos;
   char pick;
}picker;
struct lines{
  SDL_Surface * line;
  SDL_Rect linePos;
};
typedef struct{
  SDL_Surface * back;
  SDL_Rect backPos;
  SDL_Surface * x;
  SDL_Surface * o;
  SDL_Rect input;
  SDL_Surface * backbut;
  SDL_Rect backbutPos;
  SDL_Rect scorePos;
  SDL_Surface * backScore;
  SDL_Rect backScorePos;
  SDL_Surface * status;
  SDL_Rect statusPos;
  struct lines l[8];
}playgameScreen;
int initPickScreen(picker *p, SDL_Surface * screen);
picker getPick (SDL_Surface * screen, SDL_Event event, picker p);
void init (char (*m)[3]);
void computerBrain(char (*m)[3], int *xc, int *yc, int (*t)[3], int (*ta)[3], char whatComputerChose);
void initDeffTable(int (*t)[3]);
void initAttTable(int (*ta)[3]);
playgameScreen initGamePlay();
int player(char (*m)[3],SDL_Surface *screen, playgameScreen pgs, char c);
void showGamePlay(playgameScreen pgs,SDL_Surface *screen, char c);
void printOnTable(computerEnteries ce, char (*m)[3], SDL_Surface * screen, playgameScreen pgs, char c);
int checkfin(char (*m)[3]);
void checkwin(char (*m)[3], int *winner,char whatComputerChose, int *won,SDL_Surface * screen, playgameScreen pgs);
void manageScore (int winner , int *splayer1, int *splayer2);
void showScore(int winner, int scomputer, int splayer,SDL_Surface * screen, playgameScreen pgs, int whichMode);

#endif
