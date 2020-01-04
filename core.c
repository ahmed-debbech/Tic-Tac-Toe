/**
 * @file core.c
 * @author Ahmed Debbech
 * @brief Core algorithms that make the game works.
 */
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "core.h"
#include <time.h>
#include <string.h>
#include <dirent.h>
/**
 * @brief Initializes and loads all the images needed into memory to show the pick screen.
 * @param[out] picker * p the structure that will be returned if the initialization done correctly.
 * @return integer that says it the initialization done correctly (1 for done 0 for not done).
 */
int initPickScreen(picker *p){
  p->backPicker = IMG_Load("Resources/picker.png");
  p->backbut = IMG_Load("Resources/back.png");
  p->backbut2 = IMG_Load("Resources/back2.png");
  if((p->backPicker == NULL) || (p->backbut == NULL) || (p->backbut2 == NULL)){
    printf("couldn't load images\n");
    return 0;
  }else{
    p->backPos.x = 0; p->backPos.y = 0;
    p->backPos.h = p->backPicker->h; p->backPos.w = p->backPicker->w;
    p->backbutPos.x = 10; p->backbutPos.y = 455;
    p->backbutPos.h = p->backbut->h ; p->backbutPos.w = p->backbut->w;
 }
return 1;
}
/**
 * @brief Shows the pick screen and gets the event from user and analyses it.
 * @param[in] picker the structure that contains all the needed entities to show .
 * @param[in] SDL_event event the event that will put in the picker structure what did the user choose.
 * @param[in] SDL_Surface *screen the screen to blit on and show.
 * @param[in] soundFX sfx the sounds that will be generated.
 * @return it will return a picker structure that contains a field filled with what did the user choose.
 * @detail This function will return a character 'x' if user clicked on X on the screen or 'o' if clicked on O or 'n' character if user clicked back button or 'f' by default.
 */
picker getPick (SDL_Surface * screen, SDL_Event event, picker p, soundFX sfx){
  //deciding what background (theme) should be applied when openning this section.
  FILE* f = fopen("backup/general.toe", "rb");
  char themePath[256];
  fread(&themePath, sizeof(char)*256,1, f);
  fclose(f);
  SDL_Surface * back = IMG_Load(themePath);
  SDL_Rect backPos;
  backPos.x = 0; backPos.y = 0;
  backPos.h = back->h; backPos.w = back->w;
  SDL_BlitSurface(back, NULL, screen, &backPos);

  static int blitCheck = 0; // this variable for checking when to blit
  //show
  if(blitCheck == 0){
    SDL_BlitSurface(back, NULL, screen, &backPos);
  SDL_BlitSurface(p.backPicker, NULL, screen, &p.backPos);
  SDL_BlitSurface(p.backbut, NULL, screen, &p.backbutPos);
  SDL_Flip(screen);
  }
  if(event.type == SDL_MOUSEMOTION){
    if(((event.motion.x <= (p.backbutPos.x + p.backbut->w)) && (event.motion.x >= p.backbutPos.x)) && ((event.motion.y >= p.backbutPos.y) && (event.motion.y <= (p.backbutPos.y + p.backbut->h)))) {
    p.backbutPos.h = p.backbut2->h;
    p.backbutPos.w = p.backbut2->w;
    SDL_BlitSurface(back, NULL, screen, &backPos);
    SDL_BlitSurface(p.backPicker, NULL, screen, &p.backPos);
    SDL_BlitSurface(p.backbut2 ,NULL,screen,&p.backbutPos);
    if(sfx.soundMuted == 0){
   Mix_PlayChannel(-1, sfx.butHover, 0);
   }
    SDL_Flip(screen);
    blitCheck=1;
  }else{
    blitCheck = 0;
  }
}else{
    if(event.type == SDL_MOUSEBUTTONDOWN){
      if(((event.button.x <= (p.backbutPos.x + p.backbut->w)) && (event.button.x >= p.backbutPos.x)) && ((event.button.y >= p.backbutPos.y) && (event.button.y <= (p.backbutPos.y + p.backbut->h)))) {
      p.pick = 'n';
      if(sfx.soundMuted == 0){
     Mix_PlayChannel(-1, sfx.butClick, 0);
     }
      return p;
    }else{
      if(((event.button.x <= (64 + 147)) && (event.button.x >= 64)) && ((event.button.y >= 144) && (event.button.y <= ( 144+ 134)))) {
        p.pick = 'x';
        if(sfx.soundMuted == 0){
       Mix_PlayChannel(-1, sfx.butClick, 0);
       }
        return p;
      }else{
        if(((event.button.x <= (295 + 147)) && (event.button.x >= 295)) && ((event.button.y >= 144) && (event.button.y <= (144 + 134)))) {
           p.pick = 'o';
           if(sfx.soundMuted == 0){
          Mix_PlayChannel(-1, sfx.butClick, 0);
          }
           return p;
        }
      }
    }
    }
  }
p.pick = 'f';
  return p;
}
/**
 * @brief initializes the deffence table to 0.
 * @param[out] int t[3][3] returned deffence table.
 * @return nothing
 * @details This function must be called inside of computerBrain() to that function run properly.
 */
void initDeffTable(int (*t)[3]){
    int i,j;
    for (i=0; i<=2; i++) {
        for (j=0; j<=2; j++) {
            t[i][j] = 0;
        }
    }
}
/**
 * @brief initializes the attack table to 0.
 * @param[out] int ta[3][3] returned attack table.
 * @return nothing
 * @details This function must be called inside of computerBrain() to that function run properly.
 */
void initAttTable(int (*ta)[3]){
    int i,j;
    for (i=0; i<=2; i++) {
        for (j=0; j<=2; j++) {
            ta[i][j] = 0;
        }
    }
}
struct Node{
    computerEnteries turnPos;
    int numOfPlaces;
    char turn;
    struct Node * childs[9];
};
typedef struct Node node;
int checkFreePlaces(char (*m)[3]){
  int count = 0,i,j;
  for(i = 0; i<=2; i++){
    for(j = 0; j<=2; j++){
      if(m[i][j] == ' '){
        count++;
      }
    }
  }
  return count;
}
int isWin(char (*m)[3], char player){
  int i,j;
  //rows
  if((m[0][0]==player && m[0][1]==player && m[0][2]==player )||
   (m[1][0]==player && m[1][1]==player && m[1][2]==player) ||
    (m[2][0]==player && m[2][1]==player && m[2][2]==player) ||
  //columns
    (m[0][0]==player && m[1][0]==player && m[2][0]==player )||
   (m[0][1]==player && m[1][1]==player && m[2][1]==player) ||
    (m[0][2]==player && m[1][2]==player && m[2][2]==player) ||
    //diagonals
    (m[0][0]==player && m[1][1]==player && m[2][2]==player) ||
    (m[2][0]==player && m[1][1]==player && m[0][2]==player) ){

      return 1;
  }else{
    return 0;
  }
}
 computerEnteries availPlacesCoord(char (*m)[3]){
   computerEnteries ce;
  int i,j;
  for(i = 0; i<=2; i++){
    for(j = 0; j<=2; j++){
      if(m[i][j] == ' '){
        ce.xc = i;
        ce.yc = j;
        return ce;
      }
    }
  }
}
void print2DUtil(node *root, int space, int k) { 
    // Base case 
    if (root == NULL) 
        return; 
  
    // Increase distance between levels 
    space += 10; 
  
    // Process right child first 
    print2DUtil(root->childs[0], space, 0); 
  
    // Print current node after space 
    // count 
    printf("\n"); 
    for (int i = 10; i < space; i++) 
        printf(" "); 
    printf("%d\n", root->numOfPlaces); 
  
    // Process left child 
    //for(){
      print2DUtil(root->childs[k], space, k++); 
    //}
} 
void graphics(char (*m)[3]){
    printf("      1     2     3\n");
    printf("   ---------------------\n");
    printf("   y  1     2     3\n");
    printf(" x --------------------\n");
    printf(" 1 |  %c  |   %c  |  %c  |\n", m[0][0],m[0][1],m[0][2]);
    printf("   ---------------------\n");
    printf("   --------------------\n");
    printf(" 2 |  %c  |   %c  |  %c  |\n", m[1][0],m[1][1],m[1][2]);
    printf("   ---------------------\n");
    printf("   --------------------\n");
    printf(" 3 |  %c  |   %c  |  %c  |\n", m[2][0],m[2][1],m[2][2]);
    printf("   ---------------------\n");
    printf("   --------------------\n");
    printf("\n");
}
node * buildTree(char (*m)[3], int i, char player, int available){
  node * root = NULL;
  printf("====NEW FUNCTION CALL=====\n");
  if((checkfin(m) == 1) || (isWin(m, player) == 1)){
    printf("end of a path.\n");
    return NULL;
  }else{
    if(root == NULL){
      i=0;
      root = malloc(sizeof(node));
      printf("new node is allocated\n\n");
      root->turnPos = availPlacesCoord(m);
      root->numOfPlaces = checkFreePlaces(m);
      computerEnteries c;
      c = availPlacesCoord(m);
      m[c.xc][c.yc] = player;
      graphics(m);
      root->turn = player;
      printf("player: %c\n **", root->turn );
      if(player == 'x'){
        player = 'o';
      }else{
        player = 'x';
      }
      int r;
      for(r=0; r<=8; r++){
        root->childs[r] =NULL;
      }
      root->childs[0] = buildTree(m,i,player,checkFreePlaces(m));
      printf("the available places are: %d\n\n", checkFreePlaces(m));
      for(i=1; i<=available-1; i++){
        printf("other child node %d \n", i);
        root->childs[i] = buildTree(m,i,player,checkFreePlaces(m));
      }
    }
  }
  return root;
}
void showTree(node * root){
  if(root == NULL){
    return;
  }else{
    printf("node: %d\n", root->numOfPlaces);
    showTree(root->childs[0]);
  }
}
/**
 * @brief The brain of the computer responsable for making the computer thinks when playing vs Player.
 * @param[in] char m[3][3] the main matrix of the game.
 * @param[out] int *xc the coordinate X in the m matrix of the computer to be returned.
 * @param[out] int *yc the coordinate Y in the m matrix of the computer to be returned.
 * @param[in] int t[3][3] the deffence table.
 * @param[in] int ta[3][3] the attack table.
 * @param[in] char whatComputerChose the character that indicates by what the computer is currently playing with X or O.
 * @return nothing.
 * @details This function traverses all the possible cases in m matrix to generate what computer should set its turn.
 Here's how it works:
  It does the travers if there's two characters of the user in a row it puts number 2 in the deffence table on the correspinding coordinates of the empty case in m matrix in that row, and thus 2 is a danger point which cannot be removed from the table and the computer should immediately set its turn in that coordinate that coressponding to m matrix.
  If there's no number 2 in deffence table that means there's nothing to worry about and it should now attack and it will do the travers again but now if there's two characters of the computer in a row it will put number 2 in the attack table that idicates there's an oppertunity to win.
  If nothing is set from the above it will build a line to win by travers again and see if there's a row in any direction that contains its character or empty then it will play.
 */
void computerBrain(char (*m)[3], int *xc, int *yc, int (*t)[3], int (*ta)[3], char whatComputerChose){
    node * root = NULL;
    char m_holder[3][3];
    int i,j;
    for(i=0; i<=2; i++){
      for(j=0; j<=2; j++){
        m_holder[i][j] = m[i][j];
      }
    }
    root = malloc(sizeof(node));
    root->turnPos.xc = -1;
    root->numOfPlaces = checkFreePlaces(m);
    int r;
      for(r=0; r<=8; r++){
        root->childs[r] =NULL;
      }
      root->turn = whatComputerChose;
    root->childs[0]= buildTree(m_holder, 0, whatComputerChose, checkFreePlaces(m_holder));
    printf("root node: %d, %c\n", root->numOfPlaces, root->turn);
    showTree(root->childs[0]);
    printf("man\n");
}
/**
 * @brief initializes the main m matrix to spaces.
 * @param[out] char m[3][3] returned main board table.
 * @return nothing
 * @details This function must be called inside of computerBrain() to that function run properly.
 */
void init (char (*m)[3]){
    int i,j;
    for (i=0; i<=2; i++) {
        for(j=0; j<=2; j++){
            m[i][j] = ' ';
        }
    }
}
/**
 * @brief Initializes and loads all the images needed into memory to show the main board of game play.
 * @return A structure playgameScreen containing all the necesseary entities.
 */
playgameScreen initGamePlay(){
  playgameScreen pgs;
  int i;
  char name[50];
  FILE * f = NULL;
  char themePath[256];
  pgs.back = IMG_Load("Resources/playback.png");
  pgs.x = IMG_Load("Resources/x.png");
  pgs.o = IMG_Load("Resources/o.png");
  pgs.splashCharIndicatorO = IMG_Load("Resources/youplaywitho.png");
  pgs.splashCharIndicatorX = IMG_Load("Resources/youplaywithx.png");
  pgs.backbut = IMG_Load("Resources/back.png");
  pgs.backScore = IMG_Load("Resources/backscore.png");
  if((pgs.back == NULL) || (pgs.x == NULL) || (pgs.o == NULL)
   || (pgs.backbut == NULL) || (pgs.backScore == NULL)){
    printf("cant load images\n");
  }

  //initializing all the win-lines
  for (i = 0; i < 8; i++) {
    sprintf(name, "Resources/lines/line%d.png", i+1);
    pgs.l[i].line = IMG_Load(name);
    if(pgs.l[i].line == NULL){
      printf("error occured\n");
    }else{
      switch (i) {
        case 0:
         pgs.l[0].linePos.x = 75;
         pgs.l[0].linePos.y = 77;
         pgs.l[0].linePos.h = pgs.l[0].line->h ;
         pgs.l[0].linePos.w = pgs.l[0].line->w ;
        break;
        case 1:
         pgs.l[1].linePos.x = 250;
         pgs.l[1].linePos.y = 77;
         pgs.l[1].linePos.h = pgs.l[1].line->h ;
         pgs.l[1].linePos.w = pgs.l[1].line->w ;
        break;
        case 2:
        pgs.l[2].linePos.x = 89;
        pgs.l[2].linePos.y = 79;
        pgs.l[2].linePos.h = pgs.l[2].line->h ;
        pgs.l[2].linePos.w = pgs.l[2].line->w ;
        break;
        case 3:
        pgs.l[3].linePos.x =75;
        pgs.l[3].linePos.y = 245;
        pgs.l[3].linePos.h = pgs.l[3].line->h ;
        pgs.l[3].linePos.w = pgs.l[3].line->w ;
        break;
        case 4:
        pgs.l[4].linePos.x =74;
        pgs.l[4].linePos.y =137;
        pgs.l[4].linePos.h = pgs.l[4].line->h ;
        pgs.l[4].linePos.w = pgs.l[4].line->w ;
        break;
        case 5:
        pgs.l[5].linePos.x =147;
        pgs.l[5].linePos.y =77;
        pgs.l[5].linePos.h = pgs.l[5].line->h ;
        pgs.l[5].linePos.w = pgs.l[5].line->w ;
        break;
        case 6:
        pgs.l[6].linePos.x =74;
        pgs.l[6].linePos.y =352;
        pgs.l[6].linePos.h = pgs.l[6].line->h ;
        pgs.l[6].linePos.w = pgs.l[6].line->w ;
        break;
        case 7:
        pgs.l[7].linePos.x =361;
        pgs.l[7].linePos.y =77;
        pgs.l[7].linePos.h = pgs.l[7].line->h ;
        pgs.l[7].linePos.w = pgs.l[7].line->w ;
        break;
      }
    }
  }
  pgs.backbutPos.x = 10; pgs.backbutPos.y = 455;
  pgs.backbutPos.h = pgs.backbut->h ; pgs.backbutPos.w = pgs.backbut->w;
  pgs.backPos.x = 0; pgs.backPos.y = 0;
  pgs.backPos.h = pgs.back->h; pgs.backPos.w = pgs.back->w;
  pgs.backScorePos.x = 90; pgs.backScorePos.y = 428;
  pgs.backScorePos.h = pgs.backScore->h; pgs.backScorePos.w = pgs.backScore->w;
  pgs.scorePos.x = 127; pgs.scorePos.y = 433;
  pgs.splashIndicatorPos.x=100;
  pgs.splashIndicatorPos.y=150;
    pgs.splashIndicatorPos.h=pgs.splashCharIndicatorO->h;
  pgs.splashIndicatorPos.w=pgs.splashCharIndicatorO->w;

return pgs;
}
/**
 * @brief Shows and blits all the game play screen like the board.
 * @param[in] playgameScreen pgs the structure that contains all the needed entities to show .
 * @param[in] SDL_Surface * screen the screen ti blit on.
 * @return nothing
 */
void showGamePlay(playgameScreen pgs, SDL_Surface *screen){
  //deciding what background (theme) should be applied when openning this section.
  FILE* f = fopen("backup/general.toe", "rb");
  char themePath[256];
  fread(&themePath, sizeof(char)*256,1, f);
  fclose(f);
  SDL_Surface * back = IMG_Load(themePath);
  SDL_Rect backPos;
  backPos.x = 0; backPos.y = 0;
  backPos.h = back->h; backPos.w = back->w;
  SDL_BlitSurface(back, NULL, screen, &backPos);

   SDL_BlitSurface(pgs.back, NULL, screen, &pgs.backPos);
   SDL_BlitSurface(pgs.backbut, NULL, screen, &pgs.backbutPos);
}
/**
 * @brief Controls the player input and blits X or O depending on the user.
 * @param[in] char m[3][3] the main m matrix.
 * @param[in] SDL_Surface * screen the screen ti blit on.
 * @param[in] playgameScreen pgs the structure that contains all the needed entities to test the event.
 * @param[in] soundFX sfx the sounds that will be generated.
 * @return It returns -1 if the player clicked on exit button or 1 if the user played correctly or 0 if no input or 3 if back button was pressed.
 * @detail It is safe to put that function inside a do while loop and set stop case equal to zero.
 */
int player ( char (*m)[3], SDL_Surface *screen, playgameScreen pgs, char c, SDL_Event event,soundFX sfx){
  switch(event.type){
    case SDL_QUIT:
     return -1;
    break;
     case SDL_MOUSEBUTTONDOWN:
       //first case
       if(((event.button.x >= 100) && (event.button.x <= 200)) &&
       ((event.button.y >= 100) && (event.button.y <= 200))){
        if(m[0][0] == ' '){
           if(c == 'x'){
             pgs.input.x = 115;
             pgs.input.y = 115;
             pgs.input.h = pgs.x->h;
             pgs.input.w = pgs.x->w;
             m[0][0] = 'x';
           SDL_BlitSurface(pgs.x, NULL, screen, &pgs.input);
           SDL_Flip(screen);
         }else{
           pgs.input.x = 115;
           pgs.input.y = 115;
           pgs.input.h = pgs.o->h;
           pgs.input.w = pgs.o->w;
           m[0][0] = 'o';
           SDL_BlitSurface(pgs.o, NULL, screen, &pgs.input);
           SDL_Flip(screen);
         }
         if(sfx.soundMuted == 0){
        Mix_PlayChannel(-1, sfx.tap, 0);
        }
         return 1;
       }
       }else{
         //second case
         if(((event.button.x >= 207) && (event.button.x <= 303)) &&
         ((event.button.y >= 100) && (event.button.y <= 200))){
           if(m[0][1] == ' '){
           if(c == 'x'){
             pgs.input.x = 230;
             pgs.input.y = 115;
             pgs.input.h = pgs.x->h;
             pgs.input.w = pgs.x->w;
             m[0][1] = 'x';
           SDL_BlitSurface(pgs.x, NULL, screen, &pgs.input);
           SDL_Flip(screen);
         }else{
           pgs.input.x = 230;
           pgs.input.y = 115;
           pgs.input.h = pgs.o->h;
           pgs.input.w = pgs.o->w;
           m[0][1] = 'o';
           SDL_BlitSurface(pgs.o, NULL, screen, &pgs.input);
           SDL_Flip(screen);
         }
         if(sfx.soundMuted == 0){
        Mix_PlayChannel(-1, sfx.tap, 0);
        }
           return 1;
         }
         }else{
           //third case
           if(((event.button.x >= 310) && (event.button.x <= 410)) &&
           ((event.button.y >= 100) && (event.button.y <= 200))){
            if(m[0][2] == ' '){
             if(c == 'x'){
               pgs.input.x = 325;
               pgs.input.y = 115;
               pgs.input.h = pgs.x->h;
               pgs.input.w = pgs.x->w;
               m[0][2] = 'x';
             SDL_BlitSurface(pgs.x, NULL, screen, &pgs.input);
             SDL_Flip(screen);
           }else{
             pgs.input.x = 325;
             pgs.input.y = 115;
             pgs.input.h = pgs.o->h;
             pgs.input.w = pgs.o->w;
             m[0][2] = 'o';
             SDL_BlitSurface(pgs.o, NULL, screen, &pgs.input);
             SDL_Flip(screen);
           }
           if(sfx.soundMuted == 0){
          Mix_PlayChannel(-1, sfx.tap, 0);
          }
             return 1;
           }
           }else{
             //forth case
             if(((event.button.x >= 100) && (event.button.x <= 200)) &&
             ((event.button.y >= 200) && (event.button.y <= 291))){
            if(m[1][0] == ' '){
               if(c == 'x'){
                 pgs.input.x = 115;
                 pgs.input.y = 215;
                 pgs.input.h = pgs.x->h;
                 pgs.input.w = pgs.x->w;
                 m[1][0] = 'x';
               SDL_BlitSurface(pgs.x, NULL, screen, &pgs.input);
               SDL_Flip(screen);
             }else{
               pgs.input.x = 115;
               pgs.input.y = 215;
               pgs.input.h = pgs.o->h;
               pgs.input.w = pgs.o->w;
               m[1][0] = 'o';
               SDL_BlitSurface(pgs.o, NULL, screen, &pgs.input);
               SDL_Flip(screen);
             }
             if(sfx.soundMuted == 0){
            Mix_PlayChannel(-1, sfx.tap, 0);
            }
               return 1;
               }
             }else{
               //fifth case
               if(((event.button.x >= 208) && (event.button.x <= 303)) &&
               ((event.button.y >= 200) && (event.button.y <= 291))){
               if(m[1][1] == ' '){
                 if(c == 'x'){
                   pgs.input.x = 228;
                   pgs.input.y = 215;
                   pgs.input.h = pgs.x->h;
                   pgs.input.w = pgs.x->w;
                   m[1][1] = 'x';
                 SDL_BlitSurface(pgs.x, NULL, screen, &pgs.input);
                 SDL_Flip(screen);
                }else{
                 pgs.input.x = 228;
                 pgs.input.y = 215;
                 pgs.input.h = pgs.o->h;
                 pgs.input.w = pgs.o->w;
                 m[1][1] = 'o';
                 SDL_BlitSurface(pgs.o, NULL, screen, &pgs.input);
                 SDL_Flip(screen);
                }
                if(sfx.soundMuted == 0){
                Mix_PlayChannel(-1, sfx.tap, 0);
                }
                 return 1;
                 }
               }else{
                 //sixth case
                 if(((event.button.x >= 310) && (event.button.x <= 404)) &&
                 ((event.button.y >= 200) && (event.button.y <= 291))){
                   if(m[1][2] == ' '){
                   if(c == 'x'){
                     pgs.input.x = 325;
                     pgs.input.y = 215;
                     pgs.input.h = pgs.x->h;
                     pgs.input.w = pgs.x->w;
                     m[1][2] = 'x';
                   SDL_BlitSurface(pgs.x, NULL, screen, &pgs.input);
                   SDL_Flip(screen);
                  }else{
                   pgs.input.x = 325;
                   pgs.input.y = 215;
                   pgs.input.h = pgs.o->h;
                   pgs.input.w = pgs.o->w;
                   m[1][2] = 'o';
                   SDL_BlitSurface(pgs.o, NULL, screen, &pgs.input);
                   SDL_Flip(screen);
                  }
                  if(sfx.soundMuted == 0){
                 Mix_PlayChannel(-1, sfx.tap, 0);
                 }
                   return 1;
                   }
                 }else{
                   //seventh case
                   if(((event.button.x >= 100) && (event.button.x <= 200)) &&
                   ((event.button.y >= 298) && (event.button.y <= 390))){
                     if(m[2][0] == ' '){
                     if(c == 'x'){
                       pgs.input.x = 115;
                       pgs.input.y = 315;
                       pgs.input.h = pgs.x->h;
                       pgs.input.w = pgs.x->w;
                       m[2][0] = 'x';
                     SDL_BlitSurface(pgs.x, NULL, screen, &pgs.input);
                     SDL_Flip(screen);
                    }else{
                     pgs.input.x = 115;
                     pgs.input.y = 315;
                     pgs.input.h = pgs.o->h;
                     pgs.input.w = pgs.o->w;
                     m[2][0] = 'o';
                     SDL_BlitSurface(pgs.o, NULL, screen, &pgs.input);
                     SDL_Flip(screen);
                    }
                    if(sfx.soundMuted == 0){
                   Mix_PlayChannel(-1, sfx.tap, 0);
                   }
                     return 1;
                     }
                   }else{
                     //eighth case
                     if(((event.button.x >= 208) && (event.button.x <= 303)) &&
                     ((event.button.y >= 300) && (event.button.y <= 390))){
                      if(m[2][1] == ' '){
                       if(c == 'x'){
                         pgs.input.x = 215;
                         pgs.input.y = 315;
                         pgs.input.h = pgs.x->h;
                         pgs.input.w = pgs.x->w;
                         m[2][1] = 'x';
                       SDL_BlitSurface(pgs.x, NULL, screen, &pgs.input);
                       SDL_Flip(screen);
                      }else{
                       pgs.input.x = 215;
                       pgs.input.y = 315;
                       pgs.input.h = pgs.o->h;
                       pgs.input.w = pgs.o->w;
                       m[2][1] = 'o';
                       SDL_BlitSurface(pgs.o, NULL, screen, &pgs.input);
                       SDL_Flip(screen);
                      }
                      if(sfx.soundMuted == 0){
                     Mix_PlayChannel(-1, sfx.tap, 0);
                     }
                       return 1;
                     }
                     }else{
                       //ninth case
                       if(((event.button.x >= 310) && (event.button.x <= 403)) &&
                       ((event.button.y >= 300) && (event.button.y <= 390))){
                     if(m[2][2] == ' '){
                         if(c == 'x'){
                           pgs.input.x = 325;
                           pgs.input.y = 315;
                           pgs.input.h = pgs.x->h;
                           pgs.input.w = pgs.x->w;
                           m[2][2] = 'x';
                         SDL_BlitSurface(pgs.x, NULL, screen, &pgs.input);
                         SDL_Flip(screen);
                        }else{
                         pgs.input.x = 325;
                         pgs.input.y = 315;
                         pgs.input.h = pgs.o->h;
                         pgs.input.w = pgs.o->w;
                         m[2][2] = 'o';
                         SDL_BlitSurface(pgs.o, NULL, screen, &pgs.input);
                         SDL_Flip(screen);
                        }
                        if(sfx.soundMuted == 0){
                       Mix_PlayChannel(-1, sfx.tap, 0);
                       }
                         return 1;
                     }
                       }else{
                          //back button
                           if(((event.button.x <= (pgs.backbutPos.x + pgs.backbut->w)) && (event.button.x >= pgs.backbutPos.x)) && ((event.button.y >= pgs.backbutPos.y) && (event.button.y <= (pgs.backbutPos.y + pgs.backbut->h)))){
                             return 3;
                           }
                       }
                     }
                   }
                 }
               }
             }
           }
         }
       }
     break;
  }
     return 0;
}
/**
 * @brief Prints on screen the coordinates of computer.
 * @param[in] computerEnteries ce the structure contains the computer coordinates.
 * @param[in] char m[3][3] the main matrix m.
 * @param[in] SDL_Surface * screen the screen ti blit on.
 * @param[in] playgameScreen pgs the structure that contains all the needed entities to test the event.
* @pram[in] char c indicates the user's character to let the computer know what to print.
 * @return nothing
 * @detail This function is usually called after computerBrain().
 */
void printOnTable(computerEnteries ce, char (*m)[3], SDL_Surface * screen, playgameScreen pgs, char c){
  switch (ce.xc) {
    case 0:
    switch (ce.yc) {
      case 0:
      if( c == 'o'){
        pgs.input.x = 115;
        pgs.input.y = 115;
        pgs.input.h = pgs.x->h;
        pgs.input.w = pgs.x->w;
        m[0][0] = 'x';
      SDL_BlitSurface(pgs.x, NULL, screen, &pgs.input);
      SDL_Flip(screen);
    }else{
      pgs.input.x = 115;
      pgs.input.y = 115;
      pgs.input.h = pgs.o->h;
      pgs.input.w = pgs.o->w;
      m[0][0] = 'o';
      SDL_BlitSurface(pgs.o, NULL, screen, &pgs.input);
      SDL_Flip(screen);
    }
      break;
      case 1:
      if(c == 'o'){
        pgs.input.x = 230;
        pgs.input.y = 115;
        pgs.input.h = pgs.x->h;
        pgs.input.w = pgs.x->w;
        m[0][1] = 'x';
      SDL_BlitSurface(pgs.x, NULL, screen, &pgs.input);
      SDL_Flip(screen);
    }else{
      pgs.input.x = 230;
      pgs.input.y = 115;
      pgs.input.h = pgs.o->h;
      pgs.input.w = pgs.o->w;
      m[0][1] = 'o';
      SDL_BlitSurface(pgs.o, NULL, screen, &pgs.input);
      SDL_Flip(screen);
    }
      break;
      case 2:
      if(c == 'o'){
        pgs.input.x = 325;
        pgs.input.y = 115;
        pgs.input.h = pgs.x->h;
        pgs.input.w = pgs.x->w;
        m[0][2] = 'x';
      SDL_BlitSurface(pgs.x, NULL, screen, &pgs.input);
      SDL_Flip(screen);
    }else{
      pgs.input.x = 325;
      pgs.input.y = 115;
      pgs.input.h = pgs.o->h;
      pgs.input.w = pgs.o->w;
      m[0][2] = 'o';
      SDL_BlitSurface(pgs.o, NULL, screen, &pgs.input);
      SDL_Flip(screen);
    }
      break;
    }
    break;
    case 1:
    switch (ce.yc) {
      case 0:
      if(c == 'o'){
        pgs.input.x = 115;
        pgs.input.y = 215;
        pgs.input.h = pgs.x->h;
        pgs.input.w = pgs.x->w;
        m[1][0] = 'x';
      SDL_BlitSurface(pgs.x, NULL, screen, &pgs.input);
      SDL_Flip(screen);
     }else{
      pgs.input.x = 115;
      pgs.input.y = 215;
      pgs.input.h = pgs.o->h;
      pgs.input.w = pgs.o->w;
      m[1][0] = 'o';
      SDL_BlitSurface(pgs.o, NULL, screen, &pgs.input);
      SDL_Flip(screen);
     }
      break;
      case 1:
        if(c == 'o'){
          pgs.input.x = 228;
          pgs.input.y = 215;
          pgs.input.h = pgs.x->h;
          pgs.input.w = pgs.x->w;
          m[1][1] = 'x';
        SDL_BlitSurface(pgs.x, NULL, screen, &pgs.input);
        SDL_Flip(screen);
       }else{
        pgs.input.x = 228;
        pgs.input.y = 215;
        pgs.input.h = pgs.o->h;
        pgs.input.w = pgs.o->w;
        m[1][1] = 'o';
        SDL_BlitSurface(pgs.o, NULL, screen, &pgs.input);
        SDL_Flip(screen);
       }
      break;
      case 2:
      if(c == 'o'){
        pgs.input.x = 325;
        pgs.input.y = 215;
        pgs.input.h = pgs.x->h;
        pgs.input.w = pgs.x->w;
        m[1][2] = 'x';
      SDL_BlitSurface(pgs.x, NULL, screen, &pgs.input);
      SDL_Flip(screen);
     }else{
      pgs.input.x = 325;
      pgs.input.y = 215;
      pgs.input.h = pgs.o->h;
      pgs.input.w = pgs.o->w;
      m[1][2] = 'o';
      SDL_BlitSurface(pgs.o, NULL, screen, &pgs.input);
      SDL_Flip(screen);
     }
      break;
    }
    break;
    case 2:
    switch (ce.yc) {
      case 0:
      if(c == 'o'){
        pgs.input.x = 115;
        pgs.input.y = 315;
        pgs.input.h = pgs.x->h;
        pgs.input.w = pgs.x->w;
        m[2][0] = 'x';
      SDL_BlitSurface(pgs.x, NULL, screen, &pgs.input);
      SDL_Flip(screen);
     }else{
      pgs.input.x = 115;
      pgs.input.y = 315;
      pgs.input.h = pgs.o->h;
      pgs.input.w = pgs.o->w;
      m[2][0] = 'o';
      SDL_BlitSurface(pgs.o, NULL, screen, &pgs.input);
      SDL_Flip(screen);
     }
      break;
      case 1:
      if(c == 'o'){
        pgs.input.x = 215;
        pgs.input.y = 315;
        pgs.input.h = pgs.x->h;
        pgs.input.w = pgs.x->w;
        m[2][1] = 'x';
      SDL_BlitSurface(pgs.x, NULL, screen, &pgs.input);
      SDL_Flip(screen);
      }else{
      pgs.input.x = 215;
      pgs.input.y = 315;
      pgs.input.h = pgs.o->h;
      pgs.input.w = pgs.o->w;
      m[2][1] = 'o';
      SDL_BlitSurface(pgs.o, NULL, screen, &pgs.input);
      SDL_Flip(screen);
      }
      break;
      case 2:
      if(c == 'o'){
        pgs.input.x = 325;
        pgs.input.y = 315;
        pgs.input.h = pgs.x->h;
        pgs.input.w = pgs.x->w;
        m[2][2] = 'x';
      SDL_BlitSurface(pgs.x, NULL, screen, &pgs.input);
      SDL_Flip(screen);
     }else{
      pgs.input.x = 325;
      pgs.input.y = 315;
      pgs.input.h = pgs.o->h;
      pgs.input.w = pgs.o->w;
      m[2][2] = 'o';
      SDL_BlitSurface(pgs.o, NULL, screen, &pgs.input);
      SDL_Flip(screen);
     }
      break;
    }
    break;
  }
}
/**
 * @brief Checks if the matrix m is full.
 * @param[in] char m[3][3] the m matrix.
 * @detail This function should be called as a condition of the game loop .
 * @return It returns 1 if the matrix is full or o if it is not yet.
 */
int checkfin(char (*m)[3]){
    int i,j;
    for (i=0; i<=2; i++) {
        for (j=0; j<=2; j++) {
            if (m[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}
/**
 * @brief Checks for who won by traversing the matrix looking for three charactes in a row, as well as prints a line when it finds a winner.
 * @param[in] char m[3][3] the m matrix.
 * @param[out] int *winner it will be returned if it contains 1 then it is the computer won (or player1 in friend mode) or 2 if the player won (or player 2 in friend mode).
* @param[in] char whatComputerChose what is the character of the computer.
* @param[out] int *won if there's a winner returns 1 else 0.
* @param[in] SDL_Surface * screen the screen ti blit on.
* @param[in] playgameScreen pgs the structure needed to get the lines for winners.
 * @detail This function should be called as a condition of the game loop .
 * @return nothing.
 */
void checkwin(char (*m)[3], int * winner,char whatComputerChose, int *won, SDL_Surface * screen, playgameScreen pgs){
    int i,count,j;
    //for X===========
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[0][i] == 'x'){
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        if(whatComputerChose == 'x'){
          *winner = 1;
        }else{
          *winner = 2;
        }
        SDL_BlitSurface(pgs.l[4].line, NULL, screen, &pgs.l[4].linePos);
        SDL_Flip(screen);
        return;
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[i][0] == 'x') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        if(whatComputerChose == 'x'){
          *winner = 1;
        }else{
          *winner = 2;
        }
        SDL_BlitSurface(pgs.l[5].line, NULL, screen, &pgs.l[5].linePos);
        SDL_Flip(screen);
          return;
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[i][i] == 'x') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        if(whatComputerChose == 'x'){
          *winner = 1;
        }else{
          *winner = 2;
        }
        SDL_BlitSurface(pgs.l[0].line, NULL, screen, &pgs.l[0].linePos);
        SDL_Flip(screen);
          return;
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[2][i] == 'x') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        if(whatComputerChose == 'x'){
          *winner = 1;
        }else{
          *winner = 2;
        }
        SDL_BlitSurface(pgs.l[6].line, NULL, screen, &pgs.l[6].linePos);
        SDL_Flip(screen);
          return;
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[1][i] == 'x') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        if(whatComputerChose == 'x'){
          *winner = 1;
        }else{
          *winner = 2;
        }
        SDL_BlitSurface(pgs.l[3].line, NULL, screen, &pgs.l[3].linePos);
        SDL_Flip(screen);
          return;
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[i][1] == 'x') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        if(whatComputerChose == 'x'){
          *winner = 1;
        }else{
          *winner = 2;
        }
        SDL_BlitSurface(pgs.l[1].line, NULL, screen, &pgs.l[1].linePos);
        SDL_Flip(screen);
          return;
    }
    count = 0; j = 0;
    for (i=2; i>=0; i--) {
        if (m[i][j] == 'x') {
            count++;
        }
        j++;
    }
    if (count == 3) {
        *won = 1;
        if(whatComputerChose == 'x'){
          *winner = 1;
        }else{
          *winner = 2;
        }
        SDL_BlitSurface(pgs.l[2].line, NULL, screen, &pgs.l[2].linePos);
        SDL_Flip(screen);
          return;
    }
    count = 0;
    for (i=2; i>=0; i--) {
        if (m[i][2] == 'x') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        if(whatComputerChose == 'x'){
          *winner = 1;
        }else{
          *winner = 2;
        }
        SDL_BlitSurface(pgs.l[7].line, NULL, screen, &pgs.l[7].linePos);
        SDL_Flip(screen);
          return;
    }
    //for O ==========
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[0][i] == 'o') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        if(whatComputerChose == 'o'){
          *winner = 1;
        }else{
          *winner = 2;
        }
        SDL_BlitSurface(pgs.l[4].line, NULL, screen, &pgs.l[4].linePos);
        SDL_Flip(screen);
          return;
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[i][0] == 'o') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        if(whatComputerChose == 'o'){
          *winner = 1;
        }else{
          *winner = 2;
        }
        SDL_BlitSurface(pgs.l[5].line, NULL, screen, &pgs.l[5].linePos);
        SDL_Flip(screen);
          return;
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[i][i] == 'o') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        if(whatComputerChose == 'o'){
          *winner = 1;
        }else{
          *winner = 2;
        }
        SDL_BlitSurface(pgs.l[0].line, NULL, screen, &pgs.l[0].linePos);
        SDL_Flip(screen);
          return;
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[2][i] == 'o') {
          count++;
        }
    }
    if (count == 3) {
        *won = 1;
        if(whatComputerChose == 'o'){
          *winner = 1;
        }else{
          *winner = 2;
        }
        SDL_BlitSurface(pgs.l[6].line, NULL, screen, &pgs.l[6].linePos);
        SDL_Flip(screen);
          return;
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[1][i] == 'o') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        if(whatComputerChose == 'o'){
          *winner = 1;
        }else{
          *winner = 2;
        }
        SDL_BlitSurface(pgs.l[3].line, NULL, screen, &pgs.l[3].linePos);
        SDL_Flip(screen);
          return;
    }
    count = 0;
    for (i=0; i<=2; i++) {
      if (m[i][1] == 'o') {
        count++;
      }
    }
    if (count == 3) {
        *won = 1;
        if(whatComputerChose == 'o'){
          *winner = 1;
        }else{
          *winner = 2;
        }
        SDL_BlitSurface(pgs.l[1].line, NULL, screen, &pgs.l[1].linePos);
        SDL_Flip(screen);
          return;
    }
    count = 0; j = 0;
    for (i=2; i>=0; i--) {
        if (m[i][j] == 'o') {
            count++;
        }
        j++;
    }
    if (count == 3) {
        *won = 1;
        if(whatComputerChose == 'o'){
          *winner = 1;
        }else{
          *winner = 2;
        }
        SDL_BlitSurface(pgs.l[2].line, NULL, screen, &pgs.l[2].linePos);
        SDL_Flip(screen);
          return;
    }
    count = 0;
    for (i=2; i>=0; i--) {
        if (m[i][2] == 'o') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        if(whatComputerChose == 'o'){
          *winner = 1;
        }else{
          *winner = 2;
        }
        SDL_BlitSurface(pgs.l[7].line, NULL, screen, &pgs.l[7].linePos);
        SDL_Flip(screen);
          return;
    }
}
/**
 * @brief it mananages score depending on the winner.
 * @param[in] int *scomputer Score of the computer (or player1 on friend mode).
 * @param[in] int *splayer Score of the user (or player2 on friend mode).
 * @param[in] SDL_Surface * screen the screen to blit on.
 * @param[in] playgameScreen pgs the structure needed to print the score.
 * @paran[in] int winner Used to say which one has been won.
 * @detail This function should be called as a condition of the game loop .
 * @return nothing.
 */
void showScore(int winner,int scomputer, int splayer,SDL_Surface * screen, playgameScreen pgs, int whichMode){
  //if winner is 1 then it is computer else player
  // if whichMode is equal to 0 than it is computer mode else friend mode
  if(whichMode == 0){
    if (winner == 1) {
        char ch[128];
        SDL_Surface *scoring = NULL;
        TTF_Font *police = NULL;
        SDL_Color noir = {0, 0, 0};
        if (TTF_Init() < 0) {
          printf("error\n");
      }else{
        police = TTF_OpenFont("Resources/font.ttf", 20);
        if (police == NULL) {
          printf("Error in opening font file\n");
        }else{
          sprintf(ch,"Computer        %d - %d        You",scomputer, splayer);
          scoring=TTF_RenderText_Solid(police, ch, noir);
          TTF_CloseFont(police);
          TTF_Quit();
        }
      }
      SDL_BlitSurface(pgs.backScore, NULL, screen, &pgs.backScorePos);
      SDL_BlitSurface(scoring, NULL, screen, &pgs.scorePos);
      SDL_Flip(screen);
    }else{
        char ch[128];
        SDL_Surface *scoring = NULL;
        TTF_Font *police = NULL;
        SDL_Color noir = {0, 0, 0};
        if (TTF_Init() < 0) {
          printf("error\n");
      }else{
        police = TTF_OpenFont("Resources/font.ttf", 20);
        if (police == NULL) {
          printf("Error in opening font file\n");
        }else{
          sprintf(ch,"Computer        %d - %d        You",scomputer, splayer);
          scoring=TTF_RenderText_Solid(police, ch, noir);
      TTF_CloseFont(police);
      TTF_Quit();
      }
      }
      SDL_BlitSurface(pgs.backScore, NULL, screen, &pgs.backScorePos);
      SDL_BlitSurface(scoring, NULL, screen, &pgs.scorePos);
      SDL_Flip(screen);
    }
  }else{
    if (winner == 1) {
        char ch[128];
        SDL_Surface *scoring = NULL;
        TTF_Font *police = NULL;
        SDL_Color noir = {0, 0, 0};
        if (TTF_Init() < 0) {
          printf("error\n");
      }else{
        police = TTF_OpenFont("Resources/font.ttf", 20);
        if (police == NULL) {
          printf("Error in opening font file\n");
        }else{
          sprintf(ch,"'X' Player     %d - %d     'O' Player",scomputer, splayer);
          scoring=TTF_RenderText_Solid(police, ch, noir);
      TTF_CloseFont(police);
      TTF_Quit();
      }
      }
      SDL_BlitSurface(pgs.backScore, NULL, screen, &pgs.backScorePos);
      SDL_BlitSurface(scoring, NULL, screen, &pgs.scorePos);
      SDL_Flip(screen);
    }else{
        char ch[128];
        SDL_Surface *scoring = NULL;
        TTF_Font *police = NULL;
        SDL_Color noir = {0, 0, 0};
        if (TTF_Init() < 0) {
          printf("error\n");
      }else{
        police = TTF_OpenFont("Resources/font.ttf", 20);
        if (police == NULL) {
          printf("Error in opening font file\n");
        }else{
          sprintf(ch,"'X' Player     %d - %d     'O' Player",scomputer, splayer);
          scoring=TTF_RenderText_Solid(police, ch, noir);
      TTF_CloseFont(police);
      TTF_Quit();
      }
      }
      SDL_BlitSurface(pgs.backScore, NULL, screen, &pgs.backScorePos);
      SDL_BlitSurface(scoring, NULL, screen, &pgs.scorePos);
      SDL_Flip(screen);
    }
  }

}
/**
 * @brief it mananages score depending on the winner.
 * @param[out] int *splayer1 Score of the computer (or player1 on friend mode).
 * @param[out] int *splayer2 Score of the user (or player2 on friend mode).
 * @paran[in] int winner Used to say which one has been won.
 * @detail This function should be called as a condition of the game loop .
 * @return nothing.
 */
void manageScore (int winner , int *splayer1, int *splayer2){
  //if winner is 1 then it is player1 else player2
    if (winner == 1) {
      (*splayer1)++;
    }else{
      (*splayer2)++;
    }
}
/**
 * @brief This function is responsable for file manipulation that stores all the points like I/O from.
 * @param[in] int flag that is meant to specify the mode of manipulation 1 for writing and 0 for reading.
 * @param[in] int points number of points to write on the file.
 * @detail This function is explicitly called inside of managePoints() and printPoint(). PS: while flag is 1 then you should pass the points as well to write them on the file.
 * @return an integer: -1 if in case of success writing, -2 if an error occured by default OR number of points after successful reading from file.
 */
int fileManipulation(int flag, int points){
  FILE * f = NULL;
  int buffer;
  //flag = 0 means reading from file
  if(flag == 0){
    f = fopen("backup/points.toe", "rb");
      fread(&buffer, sizeof(int), 1, f);
      fclose(f);
      //return num of points in case of success reading
      return buffer;

  }else{
    //flag = 1 means writing from file
      f = fopen("backup/points.toe", "wb");
      fwrite(&points, 1, sizeof(int), f);
          fclose(f);
    //return -1 in case of success writing
    return -1;
  }
  // return -2 by default in case of an error in flag
  return -2;
}
/**
 * @brief it only prints on screen number of points gained and the highest number of points gained.
 * @param[in] points p the points to print.
 * @param[in] SDL_Surface * screen the screen to blit on the surface
 * @return nothing.
 */
void printPoints (points p, SDL_Surface * screen){
  char ch[128];
  char ch1[128];
  SDL_Surface *pointsSurf = NULL;
    SDL_Surface *high_pointsSurf = NULL;
  SDL_Rect pointsPos;
  SDL_Rect high_pointsPos;
  pointsPos.x =  82;
  pointsPos.y = 55;
  high_pointsPos.x = 270 ;
  high_pointsPos.y =  55;
  TTF_Font *police = NULL;
  SDL_Color white = {255, 255, 255};
  SDL_Color red = {255, 95, 95};
  if (TTF_Init() < 0) {
    printf("error in loading font\n");
}else{
  police = TTF_OpenFont("Resources/font.ttf", 18);
  if (police == NULL) {
    printf("Error in opening font file\n");
  }else{
    p.highest_points = fileManipulation(0, p.highest_points);
    sprintf(ch,"Current Points:   %d     ", p.user_points);
    sprintf(ch1,"Highest Points:   %d", p.highest_points);
    pointsSurf=TTF_RenderText_Solid(police, ch, white);
    high_pointsSurf=TTF_RenderText_Solid(police, ch1, red);
TTF_CloseFont(police);
TTF_Quit();
}
}
SDL_BlitSurface(pointsSurf, NULL, screen, &pointsPos);
SDL_BlitSurface(high_pointsSurf, NULL, screen, &high_pointsPos);
SDL_Flip(screen);
}
/**
 * @brief The core function of managing all the points stuff NOT THE SCORE.
 * @param[out] points *p final result of both high and current points after managing.
 * @param[in] int winner indicator of who is the winner 1 if it's computer,  2 if it is user.
 * @param[in] int scomputer the score of computer.
 * @param[in] int splayer the score of user.
 * @param[in] SDL_Surface * screen the screen to print on.
 * @detail This function is explicitly make a call for fileManipulation() inside of it.
 * @return nothing.
 */
void managePoints(points *p, int winner, int scomputer, int splayer, SDL_Surface * screen){
  static int two_times_in_row = 0; // this variable is to check if the user lost two times in a row to decrease his score.
  int reciver;
  SDL_Surface * newHSwindow = NULL;
  SDL_Rect newHSwindowPos;
  //deciding what background (theme) should be applied when openning this section.
  FILE * f = fopen("backup/general.toe", "rb");
  char themePath[256];
  fread(&themePath, sizeof(char)*256,1, f);
  fclose(f);
  SDL_Surface * back = IMG_Load(themePath);
  SDL_Rect backPos;
  backPos.x = 0; backPos.y = 0;
  backPos.h = back->h; backPos.w = back->w;

  newHSwindow = IMG_Load("Resources/newscoresplash.png");
  newHSwindowPos.x = 0; newHSwindowPos.y = 0;
  newHSwindowPos.h = newHSwindow->h; newHSwindowPos.w = newHSwindow->w;
  reciver = fileManipulation(0, p->highest_points);
  //reciver >= 0 means there's a value returned from file
  if((reciver >= 0)){
  //if the user won
  if (winner == 2) {
    if(splayer >= 5){
      p->user_points += 20;
    }else{
      p->user_points += 10;
    }
    two_times_in_row = 0;
    if(reciver < p->user_points){
      fileManipulation(1, p->user_points);
      SDL_BlitSurface(back, NULL, screen, &backPos);
      SDL_BlitSurface(newHSwindow, NULL, screen, &newHSwindowPos);
      SDL_Flip(screen);
      SDL_Delay(500);
    }
  }else{
    //if the computer won
    if((p->user_points != 0) && (two_times_in_row == 2)){
      p->user_points -= 30;
    }else{
      if((p->user_points != 0) && (two_times_in_row < 2)){
       p->user_points -= 10;
       two_times_in_row++;
     }
    }
  }
}
}
/**
 * @brief It creates all files necessary to run the app if they are not found and initialize them.
 * @return nothing.
 */
void creating_files(){
  DIR * d = NULL;
  int buffer;
  int i;
  FILE * f = NULL;
  d = opendir("backup");
  if(d == NULL){
    //file that stores tics value
    system("mkdir backup");
    system("cd backup");
    f=fopen("backup/tics.toe", "wb");
    buffer = 100;
    fwrite(&buffer, 1, sizeof(int), f);
    fclose(f);
    //file that stores highest points value
    f=fopen("backup/points.toe", "wb");
    buffer = 0;
    fwrite(&buffer, 1, sizeof(int), f); fclose(f);
    //file that stores actual theme.
    f=fopen("backup/general.toe", "wb");
    char themeName[256];
    strcpy(themeName, "Resources/themes/greeness.jpg");
    fwrite(&themeName, 1, sizeof(char)*265, f); fclose(f);
    //file that store which items bought from store
    f=fopen("backup/items.toe", "wb");
      //the stop condition in the loop bellow should increment as the number of items increase.
    for(i=0; i<4; i++ ){
      buffer = 0;
      fwrite(&buffer, 1, sizeof(int), f);
    }
    fclose(f);
  }else{
    f=fopen("backup/items.toe", "rb");
    if(f == NULL){
      f=fopen("backup/items.toe", "wb");
    }
    fclose(f);
    f=fopen("backup/tics.toe", "rb");
    if(f == NULL){
      f=fopen("backup/tics.toe", "wb");
    }
    fclose(f);
    f=fopen("backup/general.toe", "rb");
    if(f = NULL){
      f=fopen("backup/general.toe", "wb");
    }
    f=fopen("backup/points.toe", "rb");
    if(f == NULL){
      f=fopen("backup/points.toe", "wb");
    }
    fclose(f);
  }
}
/**
 * @brief Adds the new amount of tics to the user's balance after reaching the desired levels in the pack.
 * @param int tics the amount of tics to add.
 * @detail It is safe to call this function inside manageLevels().
 * @return nothing.
 */
void addTicsToBalance(int tics){
  FILE * f = NULL;
  f = fopen("backup/tics.toe", "rb");
  int x;
  fread(&x, sizeof(int), 1, f);
  x = x + tics;
  fclose(f);
  f = fopen("backup/tics.toe", "wb");
  int buffer = x;
  fwrite(&buffer, 1, sizeof(int), f);
  fclose(f);
}

/**
 * @brief It creates all files necessary to run the app if they are not found and initialize them.
 * @param[in][out] int * levels number of current levels; it can increment or decrement the value and send it back.
 * @param[in] int num the number of package.
 * @paran[in] int winChecker it says 1 if the user wins or 0 if loses.
 * @return integer that says if the user reached the desired number of levels so it returns 1 and adds tics to balance or if he loses and get to zero so it returns 0 by default it returns -1 which means nothing.
 * @detail This function calls addTicsToBalance() implicitly so it adds the new amount to the balance of the user if he reached the pack levels or reduces it if he loses.
 */
 int manageLevels(int * levels, int num, int winChecker){
   int numPkg, amount;
   switch(num){
     case 1: numPkg = 6; amount = 95;
     break;
     case 2: numPkg = 11; amount = 145;
     break;
     case 3: numPkg = 15; amount = 190;
     break;
   }
   if(winChecker == 1){
     if(numPkg == (*levels)+1){
      addTicsToBalance(amount);
       return 1;
     }else{
       (*levels)++;
     }
   }else{
     (*levels)--;
     if(*levels == 0){
       FILE * f = NULL;
       int buffer;
       f = fopen("backup/tics.toe", "rb");
       fread(&buffer, sizeof(int), 1, f);
       fclose(f);
       f = fopen("backup/tics.toe", "wb");
       if(buffer >= 40){
         buffer = buffer - 40;
       }else{
           buffer  = 0;
       }
       fwrite(&buffer, 1, sizeof(int), f);
       fclose(f);
       return 0;
     }
   }
   return -1;
 }
