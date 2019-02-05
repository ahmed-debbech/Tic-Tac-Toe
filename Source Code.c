//v1.1.0 GPLv3.0 License : An Ahmed Debbech Production
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


void about (){
    printf("*********************** ABOUT *********************************\n");
    printf("I am Ahmed Debbech, 19, creator of this game, i had the idea to \n");
    printf("make a basic game in C language as long as i am studying it \n");
    printf("at University. Hope you enjoy it!\n");
    printf("Any suggestions? Any issues? contact me at debbech.ahmed@gmail.com\n");
    printf("For source-code join the community on: https://github.com/ahmed-debbech/Tic-Tac-Toe\n");
    printf("Version: 1.1.0\n");
    printf("\n");
}
void help (){
    printf("*********************** HELP *********************************\n");
    printf("So commun and simple game you have to make THREE Xs or Os in a row\n");
    printf("in any direction to win. In order to do that this game doesn't support\n");
    printf("graphic interface so you have to specify the coordinates of each try by\n");
    printf("by entering X and Y coordonates\n");
    printf("\n");
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
void init2(int (*t)[3]){
    int i,j;
    for (i=0; i<=2; i++) {
        for (j=0; j<=2; j++) {
            t[i][j] = 0;
        }
    }
}
void init2ta(int (*ta)[3]){
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
    init2(t);
    init2ta(ta);
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
            init2ta(ta);
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
                                                                }                                  }
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
void computerplaysfirst(char (*m)[3], int *xc, int *yc, int (*t)[3], int (*ta)[3],int *start){
    int i,j, count,k,l,istheremore2,isthere2,pass = 0;
    int isthere2a, istheremore2a,done;
    int xof2=-1, yof2=-1, xof22=-1, yof22=-1;
    int xof2at =-1, yof2at =-1, xof22at =-1, yof22at =-1;
    char hold;
    if (*start == 0) {
        srand((unsigned) time(NULL));
        *xc = rand() % 3;
        *yc = rand() % 3;
        *start = 1;
    }else{
    init2(t);
    init2ta(ta);
    if (*start == 1) {
        // Begin Algorithm defence
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
                if (m[j][j] == 'o') {
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
                if (m[j][0] == 'o') {
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
                if (m[1][j] == 'o') {
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
                if (m[j][0] == 'o') {
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
                if (m[j][l] == 'o') {
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
                if (m[2][j] == 'o') {
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
                if (m[j][1] == 'o') {
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
                if (m[2][j] == 'o') {
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
                if (m[j][l] == 'o') {
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
                if (m[j][2] == 'o') {
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
                if (m[1][j] == 'o') {
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
                if (m[j][2] == 'o') {
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
                if (m[2-j][l] == 'o') {
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
                if (m[0][j] == 'o') {
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
                if (m[j][1] == 'o') {
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
            init2ta(ta);
            // Begin Algorithm attack
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
                    if (m[j][j] == 'x') {
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
                    if (m[j][0] == 'x') {
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
                    if (m[1][j] == 'x') {
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
                    if (m[j][1] == 'x') {
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
                    if (m[j][l] == 'x') {
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
                    if (m[2][j] == 'x') {
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
                    if (m[j][1] == 'x') {
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
                    if (m[2][j] == 'x') {
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
                    if (m[j][l] == 'x') {
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
                    if (m[j][2] == 'x') {
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
                    if (m[1][j] == 'x') {
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
                    if (m[j][2] == 'x') {
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
                    if (m[2-j][l] == 'x') {
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
                    if (m[0][j] == 'x') {
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
                    if (m[j][1] == 'x') {
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
                if ((m[0][0] == 'x') && ((m[0][1] == ' ') || (m[0][1] == 'x')) && ((m[0][2] == ' ') || (m[0][2] == 'x'))) {
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
                    if ((m[0][0] == 'x') && ((m[1][1] == ' ') || (m[1][1] == 'x')) && ((m[2][2] == ' ') || (m[2][2] == 'x'))) {
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
                        if ((m[0][0] == 'x') && ((m[1][0] == ' ') || (m[1][0] == 'x')) && ((m[2][0] == ' ') || ((m[2][0] == 'x')))) {
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
                            if ((m[1][0] == 'x') && ((m[1][1] == ' ') || (m[1][1] == 'x')) && ((m[1][2] == ' ') || ((m[1][2] == 'x')))) {
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
                                if ((m[2][0] == 'x') && ((m[1][0] == ' ') || (m[1][0] == 'x')) && ((m[0][0] == ' ') || ((m[0][0] == 'x')))) {
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
                                    if ((m[2][0] == 'x') && ((m[1][1] == ' ') || (m[1][1] == 'x')) && ((m[0][2] == ' ') || ((m[0][2] == 'x')))) {
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
                                        if ((m[2][0] == 'x') && ((m[2][1] == ' ') || (m[2][1] == 'x')) && ((m[2][2] == ' ') || ((m[2][2] == 'x')))) {
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
                                            if ((m[2][1] == 'x') && ((m[1][1] == ' ') || (m[1][1] == 'x')) && ((m[0][1] == ' ') || ((m[0][1] == 'x')))) {
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
                                                //sixth tour =============
                                                //1st run ==========
                                                if ((m[1][2] == 'x') && ((m[1][1] == ' ') || (m[1][1] == 'x')) && ((m[1][0] == ' ') || ((m[1][0] == 'x')))) {
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
                                                    if ((m[0][2] == 'x') && ((m[1][2] == ' ') || (m[1][2] == 'x')) && ((m[1][2] == ' ') || ((m[1][2] == 'x')))) {
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
                                                        if ((m[0][2] == 'x') && ((m[1][1] == ' ') || (m[1][1] == 'x')) && ((m[2][0] == ' ') || ((m[2][0] == 'x')))) {
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
                                                            if ((m[0][2] == 'x') && ((m[0][1] == ' ') || (m[1][0] == 'x')) && ((m[0][0] == ' ') || ((m[0][0] == 'x')))) {
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
                                                                if ((((m[0][1] == 'x') && ((m[1][1] == ' ') || (m[1][1] == 'x')) && ((m[2][1] == ' ') || (m[2][1] == 'x'))) || (((m[0][0] == 'x') || (m[0][0] == ' ')) && ((m[0][2] == 'x') || (m[0][2] == ' '))))) {
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
                                                                    if ((m[1][1] == 'x') && (((m[1][0] == 'x') || (m[1][0] == ' ')) && ((m[1][2] == 'x') || (m[1][2] == ' ')))) {
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
                                                                        if ((m[1][1] == 'x') && (((m[0][1] == 'x') || (m[0][1] == ' ')) && ((m[2][1] == 'x') || (m[2][1] == ' ')))){
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
                                                                }                                  }
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
                        if (m[0][j] == 'x') {
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
                        if (m[j][j] == 'x') {
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
                        if (m[j][0] == 'x') {
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
                        if (m[1][j] == 'x') {
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
                        if (m[j][1] == 'x') {
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
                        if (m[j][l] == 'x') {
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
                        if (m[2][j] == 'x') {
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
                        if (m[j][1] == 'x') {
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
                        if (m[2][j] == 'x') {
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
                        if (m[j][l] == 'x') {
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
                        if (m[j][2] == 'x') {
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
                        if (m[1][j] == 'x') {
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
                        if (m[j][2] == 'x') {
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
                        if (m[2-j][l] == 'x') {
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
                        if (m[0][j] == 'x') {
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
                        if (m[j][1] == 'x') {
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
                            if (m[0][j] == 'x') {
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
                            if (m[j][j] == 'x') {
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
                            if (m[j][0] == 'x') {
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
                            if (m[1][j] == 'x') {
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
                            if (m[j][1] == 'x') {
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
                            if (m[j][l] == 'x') {
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
                            if (m[2][j] == 'x') {
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
                            if (m[j][1] == 'x') {
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
                            if (m[2][j] == 'x') {
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
                            if (m[j][l] == 'x') {
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
                            if (m[j][2] == 'x') {
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
                            if (m[1][j] == 'x') {
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
                            if (m[j][2] == 'x') {
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
                            if (m[2-j][l] == 'x') {
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
                            if (m[0][j] == 'x') {
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
                            if (m[j][1] == 'x') {
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
    
}
void watchscore(char winner, int *sx, int *so){
    if (winner == 'x') {
        (*sx)++;
    }else{
        (*so)++;
    }
}
void checkwin(char (*m)[3], char *winner, int *won){
    int i,count,j;
    //for X===========
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[0][i] == 'x') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        *winner = 'x';
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[i][0] == 'x') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        *winner = 'x';
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[i][i] == 'x') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        *winner = 'x';
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[2][i] == 'x') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        *winner = 'x';
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[1][i] == 'x') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        *winner = 'x';
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[i][1] == 'x') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        *winner = 'x';
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
        *winner = 'x';
    }
    count = 0;
    for (i=2; i>=0; i--) {
        if (m[i][2] == 'x') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        *winner = 'x';
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
        *winner = 'o';
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[i][0] == 'o') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        *winner = 'o';
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[i][i] == 'o') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        *winner = 'o';
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[2][i] == 'o') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        *winner = 'o';
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[1][i] == 'o') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        *winner = 'o';
    }
    count = 0;
    for (i=0; i<=2; i++) {
        if (m[i][1] == 'o') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        *winner = 'o';
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
        *winner = 'o';
    }
    count = 0;
    for (i=2; i>=0; i--) {
        if (m[i][2] == 'o') {
            count++;
        }
    }
    if (count == 3) {
        *won = 1;
        *winner = 'o';
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
void init (char (*m)[3]){
    int i,j;
    for (i=0; i<=2; i++) {
        for(j=0; j<=2; j++){
            m[i][j] = ' ';
        }
    }
}

void user (char *c, int *x, int *y, char (*m)[3]){
    char fixx[50];
    char fixy[50];
            do{
                do{
                    printf("Your turn!\n");
                    printf("Give coordinates (X,Y)\n");
                    printf("Give first coordinate: X\n");
                    scanf("%s", fixx);
                    //while to avoid buffer overflow and first char
                    while ((strlen(fixx) > 50) || ((fixx[0]>'9') || (fixx[0] < '0'))){
                         printf("\n");
                        printf("Your input is too long or it doesn't contain numbers.\n");
                        printf("Give first coordinate: X\n");
                        scanf("%s", fixx);
                    }
                    printf("\n");
                    printf("Give second coordinates: Y\n");
                    scanf("%s", fixy);
                    printf("\n");
                    //while to avoid buffer overflow and first char
                    while ((strlen(fixy) > 50) || ((fixy[0]>'9') || (fixy[0] < '0'))) {
                        printf("Your input is too long or it doesn't contain numbers.\n");
                        printf("Give second coordinate: Y\n");
                        scanf("%s", fixy);
                    }
                    
                    //str to int
                    *x = fixx[0] - '0';
                    *y = fixy[0] - '0';
                    if (((0>(*x)) || ((*x)>3)) || ((0>(*y)) || ((*y)>3))) {
                        printf("Wrong coordinats! x and y should be in range 1 to 3\n");
                    }
                }while(((0>(*x)) || ((*x)>3)) || ((0>(*y)) || ((*y)>3))) ;
                
                if (m[(*x)-1][(*y)-1] != ' ') {
                    printf("Wrong input! pick an empty case.\n");
                }
            }while(m[(*x)-1][(*y)-1] != ' ');
    
}
char launch(){
    char c;
        
    do{
        printf("Choose 'x' or 'o'\n");
        scanf(" %c", &c);
        if ((c != 'x') && (c != 'o')) {
            printf("you should choose X or O\n");
        }
    }while((c != 'x') && (c != 'o'));
    return c;
}
int main() {
    int pick,remain,x,y,xc=-1,yc=-1,won=0,sx=0,so=0,chosen=0;
        int start = 0;
    char m[3][3];
    int t[3][3];
    int ta[3][3];
    char c,winner='n';
    init(m);
    printf("********** An Ahmed Debbech Production 2019(C) v1.1.0 **********\n");
    printf("        This game has been made with fun and love!\n");
    printf("               A 3 by 3 Tic Tac Toe game.\n");
    printf("\n");
    remain = 0;
    do{
    do{
    printf("*********************** MENU *********************************\n");
    printf("Press 1 to start the game.\n");
    printf("Press 2 to show info section.\n");
    printf("Press 3 to Know how to play.\n");
    printf("Press 0 to quit.\n");
    printf("\n");
    scanf("%d", &pick);
        if ((0>pick) || (pick>3)) {
            while ((getchar()) != '\n');
            printf("You should choose from 0 to 3\n");
        }

    }while((0>pick) || (pick>3));
    switch (pick) {
        case 1:
            //init
            won = 0;
            winner = 'n';
             init(m);
            init2(t);
            init2ta(ta);
            if (chosen == 0) {
                printf("NOTE: Your choice will be always the same until you reopen the game again.\n");
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
  //=======================
            remain = 1;
            break;
        case 2:
            about();
            remain = 1;
            break;
        case 3:
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
//v1.1.0 GPLv3.0 License : An Ahmed Debbech Production
