#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "core.h"
#include <time.h>
#include <string.h>

int initPickScreen(picker *p, SDL_Surface * screen){
  //init
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
picker getPick (SDL_Surface * screen, SDL_Event event, picker p){
  static int blitCheck = 0; // this variable for checking when to blit
  //show
  if(blitCheck == 0){
  SDL_BlitSurface(p.backPicker, NULL, screen, &p.backPos);
  SDL_BlitSurface(p.backbut, NULL, screen, &p.backbutPos);
  SDL_Flip(screen);
  }
  if(event.type == SDL_MOUSEMOTION){
    if(((event.motion.x <= (p.backbutPos.x + p.backbut->w)) && (event.motion.x >= p.backbutPos.x)) && ((event.motion.y >= p.backbutPos.y) && (event.motion.y <= (p.backbutPos.y + p.backbut->h)))) {
    p.backbutPos.h = p.backbut2->h;
    p.backbutPos.w = p.backbut2->w;
    SDL_BlitSurface(p.backPicker, NULL, screen, &p.backPos);
    SDL_BlitSurface(p.backbut2 ,NULL,screen,&p.backbutPos);
    SDL_Flip(screen);
    blitCheck=1;
  }else{
    blitCheck = 0;
  }
}else{
    if(event.type == SDL_MOUSEBUTTONDOWN){
      if(((event.button.x <= (p.backbutPos.x + p.backbut->w)) && (event.button.x >= p.backbutPos.x)) && ((event.button.y >= p.backbutPos.y) && (event.button.y <= (p.backbutPos.y + p.backbut->h)))) {
      p.pick = 'n';
      return p;
    }else{
      if(((event.button.x <= (64 + 147)) && (event.button.x >= 64)) && ((event.button.y >= 144) && (event.button.y <= ( 144+ 134)))) {
        p.pick = 'x';
        return p;
      }else{
        if(((event.button.x <= (295 + 147)) && (event.button.x >= 295)) && ((event.button.y >= 144) && (event.button.y <= (144 + 134)))) {
           p.pick = 'o';
           return p;
        }
      }
    }
    }
  }
p.pick = 'f';
  return p;
}
void initDeffTable(int (*t)[3]){
    int i,j;
    for (i=0; i<=2; i++) {
        for (j=0; j<=2; j++) {
            t[i][j] = 0;
        }
    }
}
void initAttTable(int (*ta)[3]){
    int i,j;
    for (i=0; i<=2; i++) {
        for (j=0; j<=2; j++) {
            ta[i][j] = 0;
        }
    }
}
void computer(char (*m)[3], int *xc, int *yc, int (*t)[3], int (*ta)[3]){
    int i, test=0,j, count,k,l,istheremore2,isthere2,pass = 0;
    int isthere2a, istheremore2a,done;
    int xof2=-1, yof2=-1, xof22=-1, yof22=-1;
    int xof2at =-1, yof2at =-1, xof22at =-1, yof22at =-1;
    char hold;
    for(i=0; i<=2; i++){
        for(j=0; j<=2; j++) {
            if (m[i][j] != ' ') {
                test++;
            }
        }
    }
    initDeffTable(t);
    initAttTable(ta);
    if (test > 1) {
        // Begin Algorithm defence
        //first tour ===============
        count = 0;
        hold = m[0][0];
        if (hold != ' ') {
            //1st run===================
            for (j=0; j<=2; j++) {
                if (m[0][j] == 'x') {
                    count++;
                }
            }
            k=0;
            while (k<=2) {
                if ((m[0][k] == ' ') && (t[0][k] != 2)) {
                    if (count == 0) {
                        t[0][k] = count+1;
                    }else{
                        t[0][k] = count;
                    }
                }
                k++;
            }
            //2nd run===================
            count = 0;
            for (j=0; j<=2; j++) {
                if (m[j][j] == 'x') {
                    count++;
                }
            }
            k=0;
            while (k<=2) {
                if ((m[k][k] == ' ') && (t[k][k] != 2)) {
                    if (count == 0) {
                        t[k][k] = count+1;
                    }else{
                        t[k][k] = count;
                    }
                }
                k++;
            }
            //3rd run===================
            count = 0;
            for (j=0; j<=2; j++) {
                if (m[j][0] == 'x') {
                    count++;
                }
            }
            k=0;
            while (k<=2) {
                if ((m[k][0] == ' ') && (t[k][0] != 2)) {
                    if (count == 0) {
                        t[k][0] = count+1;
                    }else{
                        t[k][0] = count;
                    }
                }
                k++;
            }
        }
        //second tour ==============
        count = 0;
        hold = m[1][0];
        if (hold != ' ') {
            //1st run===================
            for (j=0; j<=2; j++) {
                if (m[1][j] == 'x') {
                    count++;
                }
            }
            k=0;
            while (k<=2) {
                if ((m[1][k] == ' ') && (t[1][k] != 2)) {
                    if (count == 0) {
                        t[1][k] = count+1;
                    }else{
                        t[1][k] = count;
                    }
                }
                k++;
            }
        }
        // third tour ===================
        count = 0;
        hold = m[2][0];
        if (hold != ' ') {
            //1st run===================
            for (j=2; j>=0; j--) {
                if (m[j][0] == 'x') {
                    count++;
                }
            }
            k=2;
            while (k>=0) {
                if ((m[k][0] == ' ') && (t[k][0] != 2)) {
                    if (count == 0) {
                        t[k][0] = count+1;
                    }else{
                        t[k][0] = count;
                    }
                }
                k--;
            }
            //2nd run===================
            count = 0;
            l=0;
            for (j=2; j>=0; j--) {
                if (m[j][l] == 'x') {
                    count++;
                }
                l++;
            }
            k=2; l=0;
            while (k>=0) {
                if ((m[k][l] == ' ') && (t[k][l] != 2)) {
                    if (count == 0) {
                        t[k][l] = count+1;
                    }else{
                        t[k][l] = count;
                    }
                }
                k--;
                l++;
            }
            //3rd run===================
            count = 0;
            for (j=0; j<=2; j++) {
                if (m[2][j] == 'x') {
                    count++;
                }
            }
            k=0;
            while (k<=2) {
                if ((m[2][k] == ' ') && (t[2][k] != 2)) {
                    if (count == 0) {
                        t[2][k] = count+1;
                    }else{
                        t[2][k] = count;
                    }
                }
                k++;
            }
        }
        //fourth tour ====================
        count = 0;
        hold = m[2][1];
        if (hold != ' ') {
            //1st run===================
            for (j=2; j>=0; j--) {
                if (m[j][1] == 'x') {
                    count++;
                }
            }
            k=2;
            while (k>=0) {
                if ((m[k][1] == ' ') && (t[k][1] != 2)) {
                    if (count == 0) {
                        t[k][1] = count+1;
                    }else{
                        t[k][1] = count;
                    }
                }
                k--;
            }
        }
        //fifth tour ====================
        count = 0;
        hold = m[2][2];
        if (hold != ' ') {
            //1st run===================
            for (j=2; j>=0; j--) {
                if (m[2][j] == 'x') {
                    count++;
                }
            }
            k=2;
            while (k>=0) {
                if ((m[2][k] == ' ') && (t[2][k] != 2)) {
                    if (count == 0) {
                        t[2][k] = count+1;
                    }else{
                        t[2][k] = count;
                    }
                }
                k--;
            }
            //2nd run==================
            count = 0; l = 2;
            for (j=2; j>=0; j--) {
                if (m[j][l] == 'x') {
                    count++;
                }
                l--;
            }
            k=2; l =2;
            while (k>=0) {
                if ((m[k][l] == ' ') && (t[k][l] != 2)) {
                    if (count == 0) {
                        t[k][l] =  count+1;
                    }else{
                        t[k][l] = count;
                    }
                }
                k--;
                l--;
            }
            //3rd run ====================
            count = 0;
            for (j=2; j>=0; j--) {
                if (m[j][2] == 'x') {
                    count++;
                }
            }
            k=2;
            while (k>=0) {
                if ((m[k][2] == ' ') && (t[k][2] != 2)) {
                    if (count == 0) {
                        t[k][2] = count+1;
                    }else{
                        t[k][2] = count;
                    }
                }
                k--;
            }
        }
        //sixth tour ====================
        count = 0;
        hold = m[1][2];
        if (hold != ' ') {
            //1st run===================
            for (j=2; j>=0; j--) {
                if (m[1][j] == 'x') {
                    count++;
                }
            }
            k=2;
            while (k>=0) {
                if ((m[1][k] == ' ') && (t[1][k] != 2)) {
                    if (count == 0) {
                        t[1][k] = count+1;
                    }else{
                        t[1][k] = count;
                    }
                }
                k--;
            }
        }
        //seventh tour ====================
        count = 0;
        hold = m[0][2];
        if (hold != ' ') {
            //1st run===================
            for (j=0; j<=2; j++) {
                if (m[j][2] == 'x') {
                    count++;
                }
            }
            k=0;
            while (k<=2) {
                if ((m[k][2] == ' ') && (t[k][2] != 2)) {
                    if (count == 0) {
                        t[k][2] = count+1;
                    }else{
                        t[k][2] = count;
                    }
                }
                k++;
            }
            //2nd run===================
            count = 0; l = 0;
            for (j=0; j<=2; j++) {
                if (m[2-j][l] == 'x') {
                    count++;
                }
                l++;
            }
            k=0; l =0;
            while (k<=2) {
                if ((m[2-k][l] == ' ') && (t[2-k][l] != 2)) {
                    if (count == 0) {
                        t[2-k][l] = count+1;
                    }else{
                        t[2-k][l] = count;
                    }
                }
                k++;
                l++;
            }
            //3rd run===================
            count = 0;
            for (j=2; j>=0; j--) {
                if (m[0][j] == 'x') {
                    count++;
                }
            }
            k=2;
            while (k>=0) {
                if ((m[0][k] == ' ') && (t[0][k] != 2)) {
                    if (count == 0) {
                        t[0][k] = count+1;
                    }else{
                        t[0][k] = count;
                    }
                }
                k--;
            }
        }
        //eighth tour ====================
        count = 0;
        hold = m[0][1];
        if (hold != ' ') {
            //1st run===================
            for (j=0; j<=2; j++) {
                if (m[j][1] == 'x') {
                    count++;
                }
            }
            k=0;
            while (k<=2) {
                if ((m[k][1] == ' ') && (t[k][1] != 2)) {
                    if (count == 0) {
                        t[k][1] = count+1;
                    }else{
                        t[k][1] = count;
                    }
                }
                k++;
            }
        }
        // end of Algortihme defence
        pass = 1;
    }else{
        do{
            srand((unsigned) time(NULL));
            *xc = rand() % 3;
            *yc = rand() % 3;
        }while(m[*xc][*yc] != ' ');
    }
    if (pass == 1) {
        //check if all are ones 1 and twos and more
        isthere2 = 0;
        isthere2=0; istheremore2=0;
        for(i=0; i<=2; i++) {
            for(j=0; j<=2; j++) {
                if (t[i][j] == 2) {
                    if (isthere2 == 1) {
                        istheremore2 = 1;
                        xof22 = i;
                        yof22 = j;
                    }else{
                        isthere2 = 1;
                        xof2 = i;
                        yof2 = j;
                    }
                }
            }
        }
        //if all are ones
        if ((isthere2 == 0) && (istheremore2 == 0)) {
            initAttTable(ta);
            // Begin Algorithm attack
            //first tour ===============
            count = 0;
            hold = m[0][0];
            if (hold != ' ') {
                //1st run===================
                for (j=0; j<=2; j++) {
                    if (m[0][j] == 'o') {
                        count++;
                    }
                }
                k=0;
                while (k<=2) {
                    if ((m[0][k] == ' ') && (ta[0][k] != 2)) {
                        if (count == 0) {
                            ta[0][k] = count+1;
                        }else{
                            ta[0][k] = count;
                        }
                    }
                    k++;
                }
                //2nd run===================
                count = 0;
                for (j=0; j<=2; j++) {
                    if (m[j][j] == 'o') {
                        count++;
                    }
                }
                k=0;
                while (k<=2) {
                    if ((m[k][k] == ' ') && (ta[k][k] != 2)) {
                        if (count == 0) {
                            ta[k][k] = count+1;
                        }else{
                            ta[k][k] = count;
                        }
                    }
                    k++;
                }
                //3rd run===================
                count = 0;
                for (j=0; j<=2; j++) {
                    if (m[j][0] == 'o') {
                        count++;
                    }
                }
                k=0;
                while (k<=2) {
                    if ((m[k][0] == ' ') && (ta[k][0] != 2)) {
                        if (count == 0) {
                            ta[k][0] = count+1;
                        }else{
                            ta[k][0] = count;
                        }
                    }
                    k++;
                }
            }
            //second tour ==============
            count = 0;
            hold = m[1][0];
            if (hold != ' ') {
                //1st run===================
                for (j=0; j<=2; j++) {
                    if (m[1][j] == 'o') {
                        count++;
                    }
                }
                k=0;
                while (k<=2) {
                    if ((m[1][k] == ' ') && (ta[1][k] != 2)) {
                        if (count == 0) {
                            ta[1][k] = count+1;
                        }else{
                            ta[1][k] = count;
                        }
                    }
                    k++;
                }
            }
            // third tour ===================
            count = 0;
            hold = m[2][0];
            if (hold != ' ') {
                //1st run===================
                for (j=2; j>=0; j--) {
                    if (m[j][1] == 'o') {
                        count++;
                    }
                }
                k=2;
                while (k>=0) {
                    if ((m[k][1] == ' ') && (ta[k][1] != 2)) {
                        if (count == 0) {
                            ta[k][1] = count+1;
                        }else{
                            ta[k][1] = count;
                        }
                    }
                    k--;
                }
                //2nd run===================
                count = 0;
                l=0;
                for (j=2; j>=0; j--) {
                    if (m[j][l] == 'o') {
                        count++;
                    }
                    l++;
                }
                k=2; l=0;
                while (k>=0) {
                    if ((m[k][l] == ' ') && (ta[k][l] != 2)) {
                        if (count == 0) {
                            ta[k][l] = count+1;
                        }else{
                            ta[k][l] = count;
                        }
                    }
                    k--;
                    l++;
                }
                //3rd run===================
                count = 0;
                for (j=0; j<=2; j++) {
                    if (m[2][j] == 'o') {
                        count++;
                    }
                }
                k=0;
                while (k<=2) {
                    if ((m[2][k] == ' ') && (ta[2][k] != 2)) {
                        if (count == 0) {
                            ta[2][k] = count+1;
                        }else{
                            ta[2][k] = count;
                        }
                    }
                    k++;
                }
            }
            //fourth tour ====================
            count = 0;
            hold = m[2][1];
            if (hold != ' ') {
                //1st run===================
                for (j=2; j>=0; j--) {
                    if (m[j][1] == 'o') {
                        count++;
                    }
                }
                k=2;
                while (k>=0) {
                    if ((m[k][1] == ' ') && (ta[k][1] != 2)) {
                        if (count == 0) {
                            ta[k][1] = count+1;
                        }else{
                            ta[k][1] = count;
                        }
                    }
                    k--;
                }
            }
            //fifth tour ====================
            count = 0;
            hold = m[2][2];
            if (hold != ' ') {
                //1st run===================
                for (j=2; j>=0; j--) {
                    if (m[2][j] == 'o') {
                        count++;
                    }
                }
                k=2;
                while (k>=0) {
                    if ((m[2][k] == ' ') && (ta[2][k] != 2)) {
                        if (count == 0) {
                            ta[2][k] = count+1;
                        }else{
                            ta[2][k] = count;
                        }
                    }
                    k--;
                }
                //2nd run==================
                count = 0; l = 2;
                for (j=2; j>=0; j--) {
                    if (m[j][l] == 'o') {
                        count++;
                    }
                    l--;
                }
                k=2; l =2;
                while (k>=0) {
                    if ((m[k][l] == ' ') && (ta[k][l] != 2)) {
                        if (count == 0) {
                            ta[k][l] =  count+1;
                        }else{
                            ta[k][l] = count;
                        }
                    }
                    k--;
                    l--;
                }
                //3rd run ====================
                count = 0;
                for (j=2; j>=0; j--) {
                    if (m[j][2] == 'o') {
                        count++;
                    }
                }
                k=2;
                while (k>=0) {
                    if ((m[k][2] == ' ') && (ta[k][2] != 2)) {
                        if (count == 0) {
                            ta[k][2] = count+1;
                        }else{
                            ta[k][2] = count;
                        }
                    }
                    k--;
                }
            }
            //sixth tour ====================
            count = 0;
            hold = m[1][2];
            if (hold != ' ') {
                //1st run===================
                for (j=2; j>=0; j--) {
                    if (m[1][j] == 'o') {
                        count++;
                    }
                }
                k=2;
                while (k>=0) {
                    if ((m[1][k] == ' ') && (ta[1][k] != 2)) {
                        if (count == 0) {
                            ta[1][k] = count+1;
                        }else{
                            ta[1][k] = count;
                        }
                    }
                    k--;
                }
            }
            //seventh tour ====================
            count = 0;
            hold = m[0][2];
            if (hold != ' ') {
                //1st run===================
                for (j=0; j<=2; j++) {
                    if (m[j][2] == 'o') {
                        count++;
                    }
                }
                k=0;
                while (k<=2) {
                    if ((m[k][2] == ' ') && (ta[k][2] != 2)) {
                        if (count == 0) {
                            ta[k][2] = count+1;
                        }else{
                            ta[k][2] = count;
                        }
                    }
                    k++;
                }
                //2nd run===================
                count = 0; l = 0;
                for (j=0; j<=2; j++) {
                    if (m[2-j][l] == 'o') {
                        count++;
                    }
                    l++;
                }
                k=0; l =0;
                while (k<=2) {
                    if ((m[2-k][l] == ' ') && (ta[2-k][l] != 2)) {
                        if (count == 0) {
                            ta[2-k][l] = count+1;
                        }else{
                            ta[2-k][l] = count;
                        }
                    }
                    k++;
                    l++;
                }
                //3rd run===================
                count = 0;
                for (j=2; j>=0; j--) {
                    if (m[0][j] == 'o') {
                        count++;
                    }
                }
                k=2;
                while (k>=0) {
                    if ((m[0][k] == ' ') && (ta[0][k] != 2)) {
                        if (count == 0) {
                            ta[0][k] = count+1;
                        }else{
                            ta[0][k] = count;
                        }
                    }
                    k--;
                }
            }
            //eighth tour ====================
            count = 0;
            hold = m[0][1];
            if (hold != ' ') {
                //1st run===================
                for (j=0; j<=2; j++) {
                    if (m[j][1] == 'o') {
                        count++;
                    }
                }
                k=0;
                while (k<=2) {
                    if ((m[k][1] == ' ') && (ta[k][1] != 2)) {
                        if (count == 0) {
                            ta[k][1] = count+1;
                        }else{
                            ta[k][1] = count;
                        }
                    }
                    k++;
                }
            }
            // end of Algortihme attack
            isthere2a = 0;
            isthere2a = 0; istheremore2a=0;
            for(i=0; i<=2; i++) {
                for(j=0; j<=2; j++) {
                    if (ta[i][j] == 2) {
                        if (isthere2a == 1) {
                            istheremore2a = 1;
                            xof22at = i;
                            yof22at = j;
                        }else{
                            isthere2a = 1;
                            xof2at = i;
                            yof2at = j;
                        }
                    }
                }
            }
            //if theres no twos in attack
            if ((isthere2 == 0) && (istheremore2 == 0)) {
                // Algorithm of bulding line to win
                //first tour ===============
                //1st run==================
                done =0;
                if ((m[0][0] == 'o') && ((m[0][1] == ' ') || (m[0][1] == 'o')) && ((m[0][2] == ' ') || (m[0][2] == 'o'))) {
                    if (m[0][1] == ' ') {
                        *xc = 0;
                        *yc = 1;
                        done = 1;
                    }else{
                        if (m[0][2] == ' ') {
                            *xc = 0;
                            *yc = 2;
                            done = 1;
                        }
                    }
                }else{
                    //2nd run===========
                    if ((m[0][0] == 'o') && ((m[1][1] == ' ') || (m[1][1] == 'o')) && ((m[2][2] == ' ') || (m[2][2] == 'o'))) {
                        if (m[1][1] == ' ') {
                            *xc = 1;
                            *yc = 1;
                            done = 1;
                        }else{
                            if (m[2][2] == ' ') {
                                *xc = 2;
                                *yc = 2;
                                done = 1;
                            }
                        }
                    }else{
                        //3rd run =========
                        if ((m[0][0] == 'o') && ((m[1][0] == ' ') || (m[1][0] == 'o')) && ((m[2][0] == ' ') || ((m[2][0] == 'o')))) {
                            if (m[1][0] == ' ') {
                                *xc = 1;
                                *yc = 0;
                                done = 1;
                            }else{
                                if (m[2][0] == ' ') {
                                    *xc = 2;
                                    *yc = 0;
                                    done = 1;
                                }
                            }
                        }else{
                            //second tour =======
                            //1st run
                            if ((m[1][0] == 'o') && ((m[1][1] == ' ') || (m[1][1] == 'o')) && ((m[1][2] == ' ') || ((m[1][2] == 'o')))) {
                                if (m[1][1] == ' ') {
                                    *xc = 1;
                                    *yc = 1;
                                    done = 1;
                                }else{
                                    if (m[1][2] == ' ') {
                                        *xc = 1;
                                        *yc = 2;
                                        done = 1;
                                    }
                                }
                            }else{
                                //third tour =======
                                //1st run
                                if ((m[2][0] == 'o') && ((m[1][0] == ' ') || (m[1][0] == 'o')) && ((m[0][0] == ' ') || ((m[0][0] == 'o')))) {
                                    if (m[1][0] == ' ') {
                                        *xc = 1;
                                        *yc = 0;
                                        done = 1;
                                    }else{
                                        if (m[0][0] == ' ') {
                                            *xc = 0;
                                            *yc = 0;
                                            done = 1;
                                        }
                                    }
                                }else{
                                    //2nd run -=============
                                    if ((m[2][0] == 'o') && ((m[1][1] == ' ') || (m[1][1] == 'o')) && ((m[0][2] == ' ') || ((m[0][2] == 'o')))) {
                                        if (m[1][1] == ' ') {
                                            *xc = 1;
                                            *yc = 1;
                                            done = 1;
                                        }else{
                                            if (m[0][2] == ' ') {
                                                *xc = 0;
                                                *yc = 2;
                                                done = 1;
                                            }
                                        }
                                    }else{
                                        //3rd run========
                                        if ((m[2][0] == 'o') && ((m[2][1] == ' ') || (m[2][1] == 'o')) && ((m[2][2] == ' ') || ((m[2][2] == 'o')))) {
                                            if (m[2][1] == ' ') {
                                                *xc = 2;
                                                *yc = 1;
                                                done = 1;
                                            }else{
                                                if (m[2][2] == ' ') {
                                                    *xc = 2;
                                                    *yc = 2;
                                                    done = 1;
                                                }
                                            }
                                        }else{
                                            //fourth tour =============
                                            //1st tour ==========
                                            if ((m[2][1] == 'o') && ((m[1][1] == ' ') || (m[1][1] == 'o')) && ((m[0][1] == ' ') || ((m[0][1] == 'o')))) {
                                                if (m[2][1] == ' ') {
                                                    *xc = 2;
                                                    *yc = 1;
                                                    done = 1;
                                                }else{
                                                    if (m[0][1] == ' ') {
                                                        *xc = 0;
                                                        *yc = 1;
                                                        done = 1;
                                                    }
                                                }
                                            }else{
                                              //fifth tour =============
                                              //1st run ==========
                                              if ((m[2][2] == 'o') && ((m[2][1] == ' ') || (m[2][1] == 'o')) && ((m[0][2] == ' ') || ((m[0][2] == 'o')))) {
                                                  if (m[2][1] == ' ') {
                                                      *xc = 2;
                                                      *yc = 1;
                                                      done = 1;
                                                  }else{
                                                      if (m[0][2] == ' ') {
                                                          *xc = 0;
                                                          *yc = 2;
                                                          done = 1;
                                                      }
                                                  }
                                              }else{
                                                  //2nd run ==========
                                                  if ((m[2][2] == 'o') && ((m[1][1] == ' ') || (m[1][1] == 'o')) && ((m[0][0] == ' ') || ((m[0][0] == 'o')))) {
                                                      if (m[1][1] == ' ') {
                                                          *xc = 1;
                                                          *yc = 1;
                                                          done = 1;
                                                      }else{
                                                          if (m[0][0] == ' ') {
                                                              *xc = 0;
                                                              *yc = 0;
                                                              done = 1;
                                                          }
                                                      }
                                                  }else{
                                                      //3rd run ========
                                                      if ((m[2][2] == 'o') && ((m[1][2] == ' ') || (m[1][2] == 'o')) && ((m[0][2] == ' ') || ((m[0][2] == 'o')))) {
                                                          if (m[1][2] == ' ') {
                                                              *xc = 1;
                                                              *yc = 2;
                                                              done = 1;
                                                          }else{
                                                              if (m[0][2] == ' ') {
                                                                  *xc = 0;
                                                                  *yc = 2;
                                                                  done = 1;
                                                              }
                                                          }
                                                        }else{
                                                //sixth tour =============
                                                //1st run ==========
                                                if ((m[1][2] == 'o') && ((m[1][1] == ' ') || (m[1][1] == 'o')) && ((m[1][0] == ' ') || ((m[1][0] == 'o')))) {
                                                    if (m[1][1] == ' ') {
                                                        *xc = 1;
                                                        *yc = 1;
                                                        done = 1;
                                                    }else{
                                                        if (m[1][0] == ' ') {
                                                            *xc = 1;
                                                            *yc = 0;
                                                            done = 1;
                                                        }
                                                    }
                                                }else{
                                                    //seventh tour =============
                                                    //1st run ==========
                                                    if ((m[0][2] == 'o') && ((m[1][2] == ' ') || (m[1][2] == 'o')) && ((m[1][2] == ' ') || ((m[1][2] == 'o')))) {
                                                        if (m[1][2] == ' ') {
                                                            *xc = 1;
                                                            *yc = 2;
                                                            done = 1;
                                                        }else{
                                                            if (m[2][2] == ' ') {
                                                                *xc = 2;
                                                                *yc = 2;
                                                                done = 1;
                                                            }
                                                        }
                                                    }else{
                                                        //2nd run ==========
                                                        if ((m[0][2] == 'o') && ((m[1][1] == ' ') || (m[1][1] == 'o')) && ((m[2][0] == ' ') || ((m[2][0] == 'o')))) {
                                                            if (m[1][1] == ' ') {
                                                                *xc = 1;
                                                                *yc = 1;
                                                                done = 1;
                                                            }else{
                                                                if (m[2][0] == ' ') {
                                                                    *xc = 2;
                                                                    *yc = 0;
                                                                    done = 1;
                                                                }
                                                            }
                                                        }else{
                                                            //3rd run ========
                                                            if ((m[0][2] == 'o') && ((m[0][1] == ' ') || (m[1][0] == 'o')) && ((m[0][0] == ' ') || ((m[0][0] == 'o')))) {
                                                                if (m[0][1] == ' ') {
                                                                    *xc = 0;
                                                                    *yc = 1;
                                                                    done = 1;
                                                                }else{
                                                                    if (m[0][0] == ' ') {
                                                                        *xc = 0;
                                                                        *yc = 0;
                                                                        done = 1;
                                                                    }
                                                                }
                                                            }else{
                                                                //eigth tour =============
                                                                //1st run =========
                                                                if ((((m[0][1] == 'o') && ((m[1][1] == ' ') || (m[1][1] == 'o')) && ((m[2][1] == ' ') || (m[2][1] == 'o'))) || (((m[0][0] == 'o') || (m[0][0] == ' ')) && ((m[0][2] == 'o') || (m[0][2] == ' '))))) {
                                                                    if (m[1][1] == ' ') {
                                                                        *xc = 1;
                                                                        *yc = 1;
                                                                        done = 1;
                                                                    }else{
                                                                        if (m[2][1] == ' ') {
                                                                            *xc = 2;
                                                                            *yc = 1;
                                                                            done = 1;
                                                                        }
                                                                    }
                                                                }else{
                                                                    //ninth tour =============
                                                                    //1st run =========
                                                                    if ((m[1][1] == 'o') && (((m[1][0] == 'o') || (m[1][0] == ' ')) && ((m[1][2] == 'o') || (m[1][2] == ' ')))) {
                                                                        if (m[1][0] == ' ') {
                                                                            *xc = 1;
                                                                            *yc = 0;
                                                                            done = 1;
                                                                        }else{
                                                                            if (m[1][2] == ' ') {
                                                                                *xc = 1;
                                                                                *yc = 2;
                                                                                done = 1;
                                                                            }
                                                                        }
                                                                    }else{
                                                                        if ((m[1][1] == 'o') && (((m[0][1] == 'o') || (m[0][1] == ' ')) && ((m[2][1] == 'o') || (m[2][1] == ' ')))){
                                                                            if (m[0][1] == ' ') {
                                                                                *xc = 0;
                                                                                *yc = 1;
                                                                                done = 1;
                                                                            }else{
                                                                                if (m[2][1] == ' ') {
                                                                                    *xc = 2;
                                                                                    *yc = 1;
                                                                                    done = 1;
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
                                              }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // End of Algorithm of bulding line to win
                }
                //if none of the above set dot in random place
                if (done == 0) {
                    done =1;
                    for (i=0; (i<=2) && (done == 1); i++) {
                        for (j=0; (j<=2) && (done == 1); j++) {
                            if (ta[i][j] == 1) {
                                *xc = i;
                                *yc = j;
                                done = 0;
                            }
                        }
                    }
                }
              }
            }else{
                //if theres only two in attack
                if ((isthere2 == 1) && (istheremore2 == 0)) {
                    *xc = xof2at;
                    *yc = yof2at;
                }else{
                    //if there's more then two in attack
                    if ((isthere2 == 1) && (istheremore2 == 1)) {
                        *xc = xof22at;
                        *yc = yof22at;
                    }
                }
            }
        }else{
            //if theres only two
            if ((isthere2 == 1) && (istheremore2 == 0)) {
                // Begin Algorithm attack
                //first tour ===============
                count = 0;
                hold = m[0][0];
                if (hold != ' ') {
                    //1st run===================
                    for (j=0; j<=2; j++) {
                        if (m[0][j] == 'o') {
                            count++;
                        }
                    }
                    k=0;
                    while (k<=2) {
                        if ((m[0][k] == ' ') && (ta[0][k] != 2)) {
                            if (count == 0) {
                                ta[0][k] = count+1;
                            }else{
                                ta[0][k] = count;
                            }
                        }
                        k++;
                    }
                    //2nd run===================
                    count = 0;
                    for (j=0; j<=2; j++) {
                        if (m[j][j] == 'o') {
                            count++;
                        }
                    }
                    k=0;
                    while (k<=2) {
                        if ((m[k][k] == ' ') && (ta[k][k] != 2)) {
                            if (count == 0) {
                                ta[k][k] = count+1;
                            }else{
                                ta[k][k] = count;
                            }
                        }
                        k++;
                    }
                    //3rd run===================
                    count = 0;
                    for (j=0; j<=2; j++) {
                        if (m[j][0] == 'o') {
                            count++;
                        }
                    }
                    k=0;
                    while (k<=2) {
                        if ((m[k][0] == ' ') && (ta[k][0] != 2)) {
                            if (count == 0) {
                                ta[k][0] = count+1;
                            }else{
                                ta[k][0] = count;
                            }
                        }
                        k++;
                    }
                }
                //second tour ==============
                count = 0;
                hold = m[1][0];
                if (hold != ' ') {
                    //1st run===================
                    for (j=0; j<=2; j++) {
                        if (m[1][j] == 'o') {
                            count++;
                        }
                    }
                    k=0;
                    while (k<=2) {
                        if ((m[1][k] == ' ') && (ta[1][k] != 2)) {
                            if (count == 0) {
                                ta[1][k] = count+1;
                            }else{
                                ta[1][k] = count;
                            }
                        }
                        k++;
                    }
                }
                // third tour ===================
                count = 0;
                hold = m[2][0];
                if (hold != ' ') {
                    //1st run===================
                    for (j=2; j>=0; j--) {
                        if (m[j][1] == 'o') {
                            count++;
                        }
                    }
                    k=2;
                    while (k>=0) {
                        if ((m[k][1] == ' ') && (ta[k][1] != 2)) {
                            if (count == 0) {
                                ta[k][1] = count+1;
                            }else{
                                ta[k][1] = count;
                            }
                        }
                        k--;
                    }
                    //2nd run===================
                    count = 0;
                    l=0;
                    for (j=2; j>=0; j--) {
                        if (m[j][l] == 'o') {
                            count++;
                        }
                        l++;
                    }
                    k=2; l=0;
                    while (k>=0) {
                        if ((m[k][l] == ' ') && (ta[k][l] != 2)) {
                            if (count == 0) {
                                ta[k][l] = count+1;
                            }else{
                                ta[k][l] = count;
                            }
                        }
                        k--;
                        l++;
                    }
                    //3rd run===================
                    count = 0;
                    for (j=0; j<=2; j++) {
                        if (m[2][j] == 'o') {
                            count++;
                        }
                    }
                    k=0;
                    while (k<=2) {
                        if ((m[2][k] == ' ') && (ta[2][k] != 2)) {
                            if (count == 0) {
                                ta[2][k] = count+1;
                            }else{
                                ta[2][k] = count;
                            }
                        }
                        k++;
                    }
                }
                //fourth tour ====================
                count = 0;
                hold = m[2][1];
                if (hold != ' ') {
                    //1st run===================
                    for (j=2; j>=0; j--) {
                        if (m[j][1] == 'o') {
                            count++;
                        }
                    }
                    k=2;
                    while (k>=0) {
                        if ((m[k][1] == ' ') && (ta[k][1] != 2)) {
                            if (count == 0) {
                                ta[k][1] = count+1;
                            }else{
                                ta[k][1] = count;
                            }
                        }
                        k--;
                    }
                }
                //fifth tour ====================
                count = 0;
                hold = m[2][2];
                if (hold != ' ') {
                    //1st run===================
                    for (j=2; j>=0; j--) {
                        if (m[2][j] == 'o') {
                            count++;
                        }
                    }
                    k=2;
                    while (k>=0) {
                        if ((m[2][k] == ' ') && (ta[2][k] != 2)) {
                            if (count == 0) {
                                ta[2][k] = count+1;
                            }else{
                                ta[2][k] = count;
                            }
                        }
                        k--;
                    }
                    //2nd run==================
                    count = 0; l = 2;
                    for (j=2; j>=0; j--) {
                        if (m[j][l] == 'o') {
                            count++;
                        }
                        l--;
                    }
                    k=2; l =2;
                    while (k>=0) {
                        if ((m[k][l] == ' ') && (ta[k][l] != 2)) {
                            if (count == 0) {
                                ta[k][l] =  count+1;
                            }else{
                                ta[k][l] = count;
                            }
                        }
                        k--;
                        l--;
                    }
                    //3rd run ====================
                    count = 0;
                    for (j=2; j>=0; j--) {
                        if (m[j][2] == 'o') {
                            count++;
                        }
                    }
                    k=2;
                    while (k>=0) {
                        if ((m[k][2] == ' ') && (ta[k][2] != 2)) {
                            if (count == 0) {
                                ta[k][2] = count+1;
                            }else{
                                ta[k][2] = count;
                            }
                        }
                        k--;
                    }
                }
                //sixth tour ====================
                count = 0;
                hold = m[1][2];
                if (hold != ' ') {
                    //1st run===================
                    for (j=2; j>=0; j--) {
                        if (m[1][j] == 'o') {
                            count++;
                        }
                    }
                    k=2;
                    while (k>=0) {
                        if ((m[1][k] == ' ') && (ta[1][k] != 2)) {
                            if (count == 0) {
                                ta[1][k] = count+1;
                            }else{
                                ta[1][k] = count;
                            }
                        }
                        k--;
                    }
                }
                //seventh tour ====================
                count = 0;
                hold = m[0][2];
                if (hold != ' ') {
                    //1st run===================
                    for (j=0; j<=2; j++) {
                        if (m[j][2] == 'o') {
                            count++;
                        }
                    }
                    k=0;
                    while (k<=2) {
                        if ((m[k][2] == ' ') && (ta[k][2] != 2)) {
                            if (count == 0) {
                                ta[k][2] = count+1;
                            }else{
                                ta[k][2] = count;
                            }
                        }
                        k++;
                    }
                    //2nd run===================
                    count = 0; l = 0;
                    for (j=0; j<=2; j++) {
                        if (m[2-j][l] == 'o') {
                            count++;
                        }
                        l++;
                    }
                    k=0; l =0;
                    while (k<=2) {
                        if ((m[2-k][l] == ' ') && (ta[2-k][l] != 2)) {
                            if (count == 0) {
                                ta[2-k][l] = count+1;
                            }else{
                                ta[2-k][l] = count;
                            }
                        }
                        k++;
                        l++;
                    }
                    //3rd run===================
                    count = 0;
                    for (j=2; j>=0; j--) {
                        if (m[0][j] == 'o') {
                            count++;
                        }
                    }
                    k=2;
                    while (k>=0) {
                        if ((m[0][k] == ' ') && (ta[0][k] != 2)) {
                            if (count == 0) {
                                ta[0][k] = count+1;
                            }else{
                                ta[0][k] = count;
                            }
                        }
                        k--;
                    }
                }
                //eighth tour ====================
                count = 0;
                hold = m[0][1];
                if (hold != ' ') {
                    //1st run===================
                    for (j=0; j<=2; j++) {
                        if (m[j][1] == 'o') {
                            count++;
                        }
                    }
                    k=0;
                    while (k<=2) {
                        if ((m[k][1] == ' ') && (ta[k][1] != 2)) {
                            if (count == 0) {
                                ta[k][1] = count+1;
                            }else{
                                ta[k][1] = count;
                            }
                        }
                        k++;
                    }
                }
                // end of Algortihme attack
                isthere2a = 0;
                isthere2a = 0; istheremore2a=0;
                for(i=0; i<=2; i++) {
                    for(j=0; j<=2; j++) {
                        if (ta[i][j] == 2) {
                            if (isthere2a == 1) {
                                istheremore2a = 1;
                                xof22at = i;
                                yof22at = j;
                            }else{
                                isthere2a = 1;
                                xof2at = i;
                                yof2at = j;
                            }
                        }
                    }
                }
                if ((isthere2a == 1) && (istheremore2a == 0)) {
                    *xc = xof2at;
                    *yc = yof2at;
                }else{
                    *xc = xof2;
                    *yc = yof2;
                }
            }else{
                //if there's more then two
                if ((isthere2 == 1) && (istheremore2 == 1)) {
                    // Begin Algorithm attack
                    //first tour ===============
                    count = 0;
                    hold = m[0][0];
                    if (hold != ' ') {
                        //1st run===================
                        for (j=0; j<=2; j++) {
                            if (m[0][j] == 'o') {
                                count++;
                            }
                        }
                        k=0;
                        while (k<=2) {
                            if ((m[0][k] == ' ') && (ta[0][k] != 2)) {
                                if (count == 0) {
                                    ta[0][k] = count+1;
                                }else{
                                    ta[0][k] = count;
                                }
                            }
                            k++;
                        }
                        //2nd run===================
                        count = 0;
                        for (j=0; j<=2; j++) {
                            if (m[j][j] == 'o') {
                                count++;
                            }
                        }
                        k=0;
                        while (k<=2) {
                            if ((m[k][k] == ' ') && (ta[k][k] != 2)) {
                                if (count == 0) {
                                    ta[k][k] = count+1;
                                }else{
                                    ta[k][k] = count;
                                }
                            }
                            k++;
                        }
                        //3rd run===================
                        count = 0;
                        for (j=0; j<=2; j++) {
                            if (m[j][0] == 'o') {
                                count++;
                            }
                        }
                        k=0;
                        while (k<=2) {
                            if ((m[k][0] == ' ') && (ta[k][0] != 2)) {
                                if (count == 0) {
                                    ta[k][0] = count+1;
                                }else{
                                    ta[k][0] = count;
                                }
                            }
                            k++;
                        }
                    }
                    //second tour ==============
                    count = 0;
                    hold = m[1][0];
                    if (hold != ' ') {
                        //1st run===================
                        for (j=0; j<=2; j++) {
                            if (m[1][j] == 'o') {
                                count++;
                            }
                        }
                        k=0;
                        while (k<=2) {
                            if ((m[1][k] == ' ') && (ta[1][k] != 2)) {
                                if (count == 0) {
                                    ta[1][k] = count+1;
                                }else{
                                    ta[1][k] = count;
                                }
                            }
                            k++;
                        }
                    }
                    // third tour ===================
                    count = 0;
                    hold = m[2][0];
                    if (hold != ' ') {
                        //1st run===================
                        for (j=2; j>=0; j--) {
                            if (m[j][1] == 'o') {
                                count++;
                            }
                        }
                        k=2;
                        while (k>=0) {
                            if ((m[k][1] == ' ') && (ta[k][1] != 2)) {
                                if (count == 0) {
                                    ta[k][1] = count+1;
                                }else{
                                    ta[k][1] = count;
                                }
                            }
                            k--;
                        }
                        //2nd run===================
                        count = 0;
                        l=0;
                        for (j=2; j>=0; j--) {
                            if (m[j][l] == 'o') {
                                count++;
                            }
                            l++;
                        }
                        k=2; l=0;
                        while (k>=0) {
                            if ((m[k][l] == ' ') && (ta[k][l] != 2)) {
                                if (count == 0) {
                                    ta[k][l] = count+1;
                                }else{
                                    ta[k][l] = count;
                                }
                            }
                            k--;
                            l++;
                        }
                        //3rd run===================
                        count = 0;
                        for (j=0; j<=2; j++) {
                            if (m[2][j] == 'o') {
                                count++;
                            }
                        }
                        k=0;
                        while (k<=2) {
                            if ((m[2][k] == ' ') && (ta[2][k] != 2)) {
                                if (count == 0) {
                                    ta[2][k] = count+1;
                                }else{
                                    ta[2][k] = count;
                                }
                            }
                            k++;
                        }
                    }
                    //fourth tour ====================
                    count = 0;
                    hold = m[2][1];
                    if (hold != ' ') {
                        //1st run===================
                        for (j=2; j>=0; j--) {
                            if (m[j][1] == 'o') {
                                count++;
                            }
                        }
                        k=2;
                        while (k>=0) {
                            if ((m[k][1] == ' ') && (ta[k][1] != 2)) {
                                if (count == 0) {
                                    ta[k][1] = count+1;
                                }else{
                                    ta[k][1] = count;
                                }
                            }
                            k--;
                        }
                    }
                    //fifth tour ====================
                    count = 0;
                    hold = m[2][2];
                    if (hold != ' ') {
                        //1st run===================
                        for (j=2; j>=0; j--) {
                            if (m[2][j] == 'o') {
                                count++;
                            }
                        }
                        k=2;
                        while (k>=0) {
                            if ((m[2][k] == ' ') && (ta[2][k] != 2)) {
                                if (count == 0) {
                                    ta[2][k] = count+1;
                                }else{
                                    ta[2][k] = count;
                                }
                            }
                            k--;
                        }
                        //2nd run==================
                        count = 0; l = 2;
                        for (j=2; j>=0; j--) {
                            if (m[j][l] == 'o') {
                                count++;
                            }
                            l--;
                        }
                        k=2; l =2;
                        while (k>=0) {
                            if ((m[k][l] == ' ') && (ta[k][l] != 2)) {
                                if (count == 0) {
                                    ta[k][l] =  count+1;
                                }else{
                                    ta[k][l] = count;
                                }
                            }
                            k--;
                            l--;
                        }
                        //3rd run ====================
                        count = 0;
                        for (j=2; j>=0; j--) {
                            if (m[j][2] == 'o') {
                                count++;
                            }
                        }
                        k=2;
                        while (k>=0) {
                            if ((m[k][2] == ' ') && (ta[k][2] != 2)) {
                                if (count == 0) {
                                    ta[k][2] = count+1;
                                }else{
                                    ta[k][2] = count;
                                }
                            }
                            k--;
                        }
                    }
                    //sixth tour ====================
                    count = 0;
                    hold = m[1][2];
                    if (hold != ' ') {
                        //1st run===================
                        for (j=2; j>=0; j--) {
                            if (m[1][j] == 'o') {
                                count++;
                            }
                        }
                        k=2;
                        while (k>=0) {
                            if ((m[1][k] == ' ') && (ta[1][k] != 2)) {
                                if (count == 0) {
                                    ta[1][k] = count+1;
                                }else{
                                    ta[1][k] = count;
                                }
                            }
                            k--;
                        }
                    }
                    //seventh tour ====================
                    count = 0;
                    hold = m[0][2];
                    if (hold != ' ') {
                        //1st run===================
                        for (j=0; j<=2; j++) {
                            if (m[j][2] == 'o') {
                                count++;
                            }
                        }
                        k=0;
                        while (k<=2) {
                            if ((m[k][2] == ' ') && (ta[k][2] != 2)) {
                                if (count == 0) {
                                    ta[k][2] = count+1;
                                }else{
                                    ta[k][2] = count;
                                }
                            }
                            k++;
                        }
                        //2nd run===================
                        count = 0; l = 0;
                        for (j=0; j<=2; j++) {
                            if (m[2-j][l] == 'o') {
                                count++;
                            }
                            l++;
                        }
                        k=0; l =0;
                        while (k<=2) {
                            if ((m[2-k][l] == ' ') && (ta[2-k][l] != 2)) {
                                if (count == 0) {
                                    ta[2-k][l] = count+1;
                                }else{
                                    ta[2-k][l] = count;
                                }
                            }
                            k++;
                            l++;
                        }
                        //3rd run===================
                        count = 0;
                        for (j=2; j>=0; j--) {
                            if (m[0][j] == 'o') {
                                count++;
                            }
                        }
                        k=2;
                        while (k>=0) {
                            if ((m[0][k] == ' ') && (ta[0][k] != 2)) {
                                if (count == 0) {
                                    ta[0][k] = count+1;
                                }else{
                                    ta[0][k] = count;
                                }
                            }
                            k--;
                        }
                    }
                    //eighth tour ====================
                    count = 0;
                    hold = m[0][1];
                    if (hold != ' ') {
                        //1st run===================
                        for (j=0; j<=2; j++) {
                            if (m[j][1] == 'o') {
                                count++;
                            }
                        }
                        k=0;
                        while (k<=2) {
                            if ((m[k][1] == ' ') && (ta[k][1] != 2)) {
                                if (count == 0) {
                                    ta[k][1] = count+1;
                                }else{
                                    ta[k][1] = count;
                                }
                            }
                            k++;
                        }
                    }
                    // end of Algortihme attack
                    isthere2a = 0;
                    isthere2a = 0; istheremore2a=0;
                    for(i=0; i<=2; i++) {
                        for(j=0; j<=2; j++) {
                            if (ta[i][j] == 2) {
                                if (isthere2a == 1) {
                                    istheremore2a = 1;
                                    xof22at = i;
                                    yof22at = j;
                                }else{
                                    isthere2a = 1;
                                    xof2at = i;
                                    yof2at = j;
                                }
                            }
                        }
                    }
                    if ((isthere2a == 1) && (istheremore2a == 0)) {
                        *xc = xof2at;
                        *yc = yof2at;
                    }else{
                        *xc = xof22;
                        *yc = yof22;
                    }
                }
            }
        }
}
}
void init (char (*m)[3]){
    int i,j;
    for (i=0; i<=2; i++) {
        for(j=0; j<=2; j++){
            m[i][j] = ' ';
        }
    }
}
playgameScreen initGamePlay(){
  playgameScreen pgs;
  int i;
  char name[50];
  pgs.back = IMG_Load("Resources/playback.png");
  pgs.x = IMG_Load("Resources/x.png");
  pgs.o = IMG_Load("Resources/o.png");
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
  pgs.scorePos.x = 156;
  pgs.scorePos.y = 23;
  pgs.statusPos.x = 263;
  pgs.statusPos.y = 456;
  pgs.backbutPos.x = 10; pgs.backbutPos.y = 455;
  pgs.backbutPos.h = pgs.backbut->h ; pgs.backbutPos.w = pgs.backbut->w;
  pgs.backPos.x = 0; pgs.backPos.y = 0;
  pgs.backPos.h = pgs.back->h; pgs.backPos.w = pgs.back->w;
  pgs.backScorePos.x = 140; pgs.backScorePos.y = 428;
  pgs.backScorePos.h = pgs.backScore->h; pgs.backScorePos.w = pgs.backScore->w;
  pgs.scorePos.x = 140; pgs.scorePos.y = 435;
return pgs;
}
void showGamePlay(playgameScreen pgs, SDL_Surface *screen, char c){
   SDL_BlitSurface(pgs.back, NULL, screen, &pgs.backPos);
   SDL_BlitSurface(pgs.backbut, NULL, screen, &pgs.backbutPos);
}
void graphics(char (*m)[3]){
    printf("   y  1     2     3\n");
    printf(" x --------------------\n");
    printf(" 1 |  %c  |   %c  |  %c  |\n", m[0][0],m[0][1],m[0][2]);
    printf("   --------------------\n");
    printf(" 2 |  %c  |   %c  |  %c  |\n", m[1][0],m[1][1],m[1][2]);
    printf("   --------------------\n");
    printf(" 3 |  %c  |   %c  |  %c  |\n", m[2][0],m[2][1],m[2][2]);
    printf("   --------------------\n");
    printf("\n");
}
int player ( char (*m)[3], SDL_Surface *screen, playgameScreen pgs, char c){
  SDL_Event event;
  SDL_WaitEvent(&event);
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
                         return 1;
                     }
                       }else{
                          //back button
                           if(((event.button.x <= (pgs.backbutPos.x + pgs.backbut->w)) && (event.button.x >= pgs.backbutPos.x)) && ((event.button.y >= pgs.backbutPos.y) && (event.button.y <= (pgs.backbutPos.y + pgs.backbut->h)))){
                             return 3;
                           }else{

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
    }
}
void showScore(int winner,char whatComputerChose,int scomputer, int splayer,SDL_Surface * screen, playgameScreen pgs){
  //if winner is 1 then it is computer else player
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
          sprintf(ch,"Computer %d - %d You",scomputer, splayer);
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
          sprintf(ch,"Computer %d - %d You",scomputer, splayer);
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
void manageScore (int winner , int *scomputer, int *splayer){
  //if winner is 1 then it is computer else player
    if (winner == 1) {
      (*scomputer)++;
    }else{
      (*splayer)++;
    }
}
