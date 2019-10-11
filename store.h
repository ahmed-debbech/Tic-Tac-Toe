#ifndef STORE_H_INCLUDED
#define STORE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
/**
 * @brief The structure that contains all about coins (tics).
 */
typedef struct{
  SDL_Surface * coinImage; /**< the image of the coin. */
  SDL_Rect coinPos; /**< the position of the coin on screen. */
   int  text; /**<text conatining the value of coins. */
}tics;
/**
 * @brief a node of singly-linked list to store all the items of store.
 */
struct node{
   SDL_Surface * theme; /**< the adress of the theme button image. */
   SDL_Rect themePos; /**< the theme image position on screen. */
   int buyCheck; /**< checking if this item was bought. */
    struct node * next; /**< pointer to the next theme button in the linked list. */
 };
 typedef struct node node_of_list_items;
 /**
  * @brief All the store elements to print on screen are here.
  */
typedef struct{
  SDL_Surface * storeBack; /**< store background image. */
  SDL_Rect storeBackPos; /**< store background image position. */
  node_of_list_items * head_of_list_items; /**< the pointer that points to the first element of the list items to show. */
}store;
node_of_list_items * retriveItems();
store initStore();
void showStore(store s, SDL_Surface * screen, buttons bu);
tics manageTics(int winner);
void printTics(tics t, SDL_Surface * screen);
int storeClicks(SDL_Event event, buttons bu, soundFX sfx);
int buyingManger(int itemSelected, SDL_Surface * screen);
#endif
