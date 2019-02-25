//v1.2.1 GPLv3.0 License : An Ahmed Debbech Production.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "implement.h"


int main() {
    int pick,remain,x,y,xc=-1,yc=-1,won=0,sx=0,so=0,chosen=0,scox = 0,
    scoo = 0, chosenfriend = 0;
    int start = 0, test = 0;
    char m[3][3], pickfriend='n';
    int t[3][3];
    int ta[3][3];
    char c,winner='n';
    init(m);
    printf("********** An Ahmed Debbech Production 2019(C) v1.2.1 **********\n");
    printf("        This game has been made with fun and love!\n");
    printf("               A 3 by 3 Tic Tac Toe game.\n");
    printf("\n");
    remain = 0;
    do{
    do{
    printf("*********************** MENU *********************************\n");
    printf("Press 1 to play with computer.\n");
    printf("Press 2 to play with a friend.\n");
    printf("Press 3 to show info section.\n");
    printf("Press 4 to know how to play.\n");
    printf("Press 0 to quit.\n");
    printf("\n");
    scanf("%d", &pick);
        if ((0>pick) || (pick>4)) {
            while ((getchar()) != '\n');
            printf("You should choose from 0 to 3\n");
        }

    }while((0>pick) || (pick>4));
    switch (pick) {
        case 1:
            //init
            won = 0;
            winner = 'n';
             init(m);
            init2(t);
            init2ta(ta);
            if (chosen == 0) {
                printf("NOTE: Your choice will be always the same until you restart the game again.\n");
               c = launch();
            }
            chosen = 1;
    //=====GAME ENGIN =========
                if (c == 'x') {
                    printf("Score: X player %d\n", sx);
                    printf("Score: O player %d\n", so);
                    printf("You are playing with X\n");
                    printf("\n");
                    graphics(m);
                    do{
                  user(&c,&x,&y,m);
                 m[x-1][y-1] = 'x';
                checkwin(m,&winner,&won);
            if ((won == 0) && (checkfin(m) == 0)){
                printf("computer's turn ...\n");
                printf("done.\n");
                computer(m,&xc,&yc,t,ta);
                m[xc][yc] = 'o';
            }
                  checkwin(m,&winner,&won);
                        graphics(m);
            }while((won == 0) && (checkfin(m) == 0));
                    if (won == 1) {
                        printf("The Winner is: %c player\n", winner);
                        watchscore(winner, &sx, &so);
                        printf("Score: X player %d\n", sx);
                        printf("Score: O player %d\n", so);
                        printf("\n");
                    }else{
                        if (checkfin(m) == 1) {
                            printf("This game has been ended by Tie!\n");
                            printf("Score: X player %d\n", sx);
                            printf("Score: O player %d\n", so);
                            printf("\n");
                        }
                    }
            }else{
                printf("Score: X player %d\n", sx);
                printf("Score: O player %d\n", so);
                printf("\n");
                printf("You are playing with O\n");
                do{
                    printf("computer's turn ...\n");
                    printf("done.\n");
                    computerplaysfirst(m, &xc, &yc, t, ta,&start);
                    m[xc][yc] = 'x';
                     checkwin(m,&winner,&won);
                    graphics(m);
                    if ((won == 0) && (checkfin(m) == 0)){
                        user(&c, &x, &y, m);
                        m[x-1][y-1] = 'o';
                    }
                    graphics(m);
                     checkwin(m,&winner,&won);
                }while((won == 0) && (checkfin(m) == 0));
                start = 0;
                if (won == 1) {
                    printf("The Winner is: %c player\n", winner);
                    watchscore(winner, &sx, &so);
                    printf("Score: X player %d\n", sx);
                    printf("Score: O player %d\n", so);
                    printf("\n");
                }else{
                    if (checkfin(m) == 1) {
                        printf("This game has been ended by Tie!\n");
                        printf("Score: X player %d\n", sx);
                        printf("Score: O player %d\n", so);
                        printf("\n");
                    }
                }
            }
            scoo = 0;
            scox = 0;
            won = 0;
  //=======================
            remain = 1;
            break;
        case 2:
            //Multi Players section
            if (chosenfriend == 0) {
                printf("NOTE: Your choice will be always the same until you restart the game again.\n");
                chosenfriend = 1;
            }
            init(m);
            if(test == 0){
            do{
              printf("Player 1 plays with : (pick from X or O)\n");
              scanf(" %c", &pickfriend);
                if ((pickfriend != 'X') && (pickfriend != 'O') && (pickfriend != 'x') && (pickfriend != 'o')) {
                    printf("Wrong Input!\n");
                }
            }while ((pickfriend != 'X') && (pickfriend != 'O') && (pickfriend != 'x') && (pickfriend != 'o'));
            if ((pickfriend == 'X') || (pickfriend == 'x')) {
                printf("Player 1 is playing with X\n");
                printf("Player 2 is playing with O\n");
                printf("\n");
                test = 1;
            }else{
                printf("Player 1 is playing with O\n");
                printf("Player 2 is playing with X\n");
                printf("\n");
                test = 1;
            }
            }
            printf("Score: X player %d\n", scox);
            printf("Score: O player %d\n", scoo);
            printf("\n");
            graphics(m);
            do{
                if ((pickfriend == 'X') || (pickfriend == 'x')) {
                    printf("Turn of X Player\n");
                }else{
                    printf("Turn of O Player\n");
                }
                playfriend(m,&x,&y);
                if ((pickfriend == 'X') || (pickfriend == 'x')) {
                    m[x-1][y-1] = 'x';
                }else{
                    m[x-1][y-1] = 'o';
                }
                checkwin(m,&winner,&won);
                if ((won == 0) && (checkfin(m) == 0)){
                    graphics(m);
                    if ((pickfriend == 'X') || (pickfriend == 'x')) {
                        printf("Turn of O Player\n");
                    }else{
                        printf("Turn of X Player\n");
                    }
                    playfriend(m,&x,&y);
                    if ((pickfriend == 'X') || (pickfriend == 'x')) {
                        m[x-1][y-1] = 'o';
                    }else{
                        m[x-1][y-1] = 'x';
                    }
                }
                checkwin(m,&winner,&won);
                graphics(m);
            }while((won == 0) && (checkfin(m) == 0));
            if (won == 1) {
                printf("The Winner is: %c player\n", winner);
                watchscore(winner, &scox, &scoo);
                printf("Score: X player %d\n", scox);
                printf("Score: O player %d\n", scoo);
                printf("\n");
            }else{
                if (checkfin(m) == 1) {
                    printf("This game has been ended by Tie!\n");
                    printf("Score: X player %d\n", scox);
                    printf("Score: O player %d\n", scoo);
                    printf("\n");
                }
            }
            won = 0;
            sx = 0;
            so = 0;
            remain = 1;
            break;
        case 3:
            about();
            remain = 1;
            break;
        case 4:
            help();
            remain = 1;
            break;
        case 0:
            printf("GOOD BYE!\n");
            remain = 0;
            break;
    }
    }while(remain == 1);
    return 0;
}
//v1.2.1 GPLv3.0 License : An Ahmed Debbech Production.
