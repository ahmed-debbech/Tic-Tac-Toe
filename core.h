
#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED
#include <stdio.h>

typedef struct{
    int xu;
    int yu;
}usercoor;
typedef struct {
    int xc;
    int yc;
}compcoor;
typedef struct{
    usercoor u;
    compcoor c;
}coordinates;

void about (void);
void help (void);
void graphics(char (*m)[3]);
void init2(int (*t)[3]);
void init2ta(int (*ta)[3]);
void computer(char (*m)[3], int *xc, int *yc, int (*t)[3], int (*ta)[3]);
void computerplaysfirst(char (*m)[3], int *xc, int *yc, int (*t)[3], int (*ta)[3],int *start);
void watchscore(char winner, int *sx, int *so);
void checkwin(char (*m)[3], char *winner, int *won);
int checkfin(char (*m)[3]);
void init (char (*m)[3]);
void user (char *c, int *x, int *y, char (*m)[3]);
char launch(void);
void playfriend(char (*m)[3], int *x, int *y);
#endif
