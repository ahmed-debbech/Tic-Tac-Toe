/**
 * @file store.c
 * @author Ahmed Debbech
 * @brief  All functions about the store.
 */
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "graphics.h"
#include "core.h"
#include "store.h"
#include <string.h>
#include <dirent.h>
/**
 * @brief Initializes a linked list full of store items (buttons) like themes.
 *@detail This function must be called inside initStore() to work properly.
 * @return A pointer to the head of the linked list and this pointer should be assigned to the specific attribute in store structure.
 */
node_of_list_items * retriveItems(){
  int i = 1;
  int text;
  char name [50];
  //these two variables below to adjust position of the right palce for each store item on screen.
  int x; int y;
  FILE * f = NULL;
  node_of_list_items * head = NULL;
  node_of_list_items * walk = NULL;
  node_of_list_items * node = NULL;
  f = fopen("backup/items.toe", "rb");
  do{
    sprintf(name, "Resources/store-items/theme%d.png", i);
        if(head == NULL){
      node = malloc(sizeof(node_of_list_items));
      node->theme = IMG_Load(name);
      x = 18; y = 141;
      if(node->theme != NULL){
      node->themePos.x = x;
      node->themePos.y = y;
      node->themePos.h = node->theme->h;
      node->themePos.w = node->theme->w;
      node->next = NULL;
      }
      head = node;
      fread(&text, sizeof(int), 1 ,f);
      node->buyCheck = text;
    }else{
      walk = head;
      while(walk->next != NULL){
        walk = walk->next;
      }
      node = malloc(sizeof(node_of_list_items));
      walk->next = node;
      node->theme = IMG_Load(name);
      fread(&text, sizeof(int), 1 ,f);
      node->buyCheck = text;
      // if the a line is complete in the grid than pass to next line
      if(node->theme != NULL){
      if(x > 250){
        y += 60;
        x = 18;
        node->themePos.x = x;
        node->themePos.y = y;
        node->themePos.h = node->theme->h;
        node->themePos.w = node->theme->w;
        node->next = NULL;
      }else{
        x += 165;
      node->themePos.x = x;
      node->themePos.y = y;
      node->themePos.h = node->theme->h;
      node->themePos.w = node->theme->w;
      node->next = NULL;
      }
    }else{
      walk->next = NULL;
    }
    }
    i++;
  }while(node->theme != NULL);
  fclose(f);
  return head;
}
/**
 * @brief Initializes all images necessary for the store of the game.
 * @return Returns a structure of store type containg all the necessary elemts to print on screen.
 */
store initStore(){
  store s;
  s.storeBack = IMG_Load("Resources/storeback.png");
  if(s.storeBack == NULL){
    printf("an error occured while oppening store, image may not be in right system path\n");
  }else{
    s.storeBackPos.x = 0;
    s.storeBackPos.y = 0;
    s.storeBackPos.h = s.storeBack->h;
    s.storeBackPos.w = s.storeBack->w;
    s.head_of_list_items = retriveItems();
  }
  return s;
}
/**
 * @brief Prints the whole store on screen.
 *@param [in] store s structure necessary to print
 *@param [in] SDL_Surface * screen screen to print on.
 *@param [in] buttons bu to print back button.
 * @return Nothing.
 */
void showStore(store s, SDL_Surface * screen, buttons bu){
  //deciding what background (theme) should be applied when openning this section.
  FILE * f = fopen("backup/general.toe", "rb");
  char themePath[256];
  fread(&themePath, sizeof(char)*256,1, f);
  fclose(f);
  SDL_Surface * back = IMG_Load(themePath);
  SDL_Rect backPos;
  backPos.x = 0; backPos.y = 0;
  backPos.h = back->h; backPos.w = back->w;
  SDL_BlitSurface(back, NULL, screen, &backPos);

  SDL_Surface * unlocked = IMG_Load("Resources/unlocked.png");
  SDL_BlitSurface(s.storeBack, NULL, screen, &s.storeBackPos);
  SDL_BlitSurface(bu.backbut, NULL, screen, &bu.backbutPos);
  node_of_list_items * head = s.head_of_list_items;
  while(head != NULL){
    if(head->theme != NULL){
    SDL_BlitSurface(head->theme, NULL, screen, &head->themePos);
     if(head->buyCheck == 1){
      SDL_BlitSurface(unlocked, NULL, screen, &head->themePos);
     }
    }
    head = head->next;
  }
  char ch[128];
  SDL_Surface *value = NULL;
  SDL_Rect valuePos;
  TTF_Font *police = NULL;
  SDL_Color color = {255, 0, 0};
    int text;
  if (TTF_Init() < 0) {
    printf("error\n");
}else{
  police = TTF_OpenFont("Resources/font.ttf", 20);
  if (police == NULL) {
    printf("Error in opening font file\n");
  }else{
    f = fopen("backup/tics.toe", "rb");
      fread(&text, sizeof(int), 1 ,f);
     sprintf(ch, "%d", text);
      value=TTF_RenderText_Solid(police, ch, color);
      TTF_CloseFont(police);
      TTF_Quit();
      fclose(f);
  }
}
valuePos.x = 250;
valuePos.y = 57;
SDL_BlitSurface(value, NULL, screen, &valuePos);
}
/**
 * @brief Responsable for managing all tics.
 *@param [in] int winner the variable that says who was the winner.
 * @return tics structure filled with all data necessary.
 */
tics manageTics(int winner){
  tics t;
  static short won_five_time_row= 0;
  FILE *f = NULL;
      f = fopen("backup/tics.toe", "rb");
      //read from file the number before erease it.
      fread(&t.text, sizeof(int), 1 ,f);
      //writing down the value considering the condition
      fclose(f);
      f = fopen("backup/tics.toe", "wb");
      if(winner == 2){
      if(won_five_time_row < 5){
       t.text += 10;
       fwrite(&t.text, 1, sizeof(int), f);
       won_five_time_row++;
    }else{
       t.text += 20;
       fwrite(&t.text, 1, sizeof(int), f);
       won_five_time_row = 0;
    }
  }else{
    won_five_time_row = 0;
  }
    fclose(f);


 return t;
}
/**
 * @brief Responsable for printing the whole store screen.
 *@param [in] tics t all the images and surfaces necessary to print.
  *@param [in] SDL_Surface * screen the pointer to the screen to print on .
 * @return tics structure filled with all data necessary.
 */
void printTics(tics t, SDL_Surface * screen){
  // making the coins value texture
  char ch[128];
  SDL_Surface *value = NULL;
  SDL_Rect valuePos;
  TTF_Font *police = NULL;
  DIR * d =NULL;
  SDL_Color color = {255, 0, 0};
  FILE * f = NULL;
  if (TTF_Init() < 0) {
    printf("error\n");
}else{
  police = TTF_OpenFont("Resources/font.ttf", 20);
  if (police == NULL) {
    printf("Error in opening font file\n");
  }else{
    f = fopen("backup/tics.toe", "rb");
      fread(&t.text, sizeof(int), 1 ,f);
     sprintf(ch, "Tics:   %d", t.text);
      value=TTF_RenderText_Solid(police, ch, color);
      TTF_CloseFont(police);
      TTF_Quit();
      fclose(f);
  }
}

//loading the tic image coin
t.coinImage = IMG_Load("Resources/coin-tic.png");
t.coinPos.x = 175;
t.coinPos.y = 466;
t.coinPos.h = t.coinImage->h;
t.coinPos.w = t.coinImage->w;
valuePos.x = 230;
valuePos.y = 466;
SDL_BlitSurface(t.coinImage, NULL, screen, &t.coinPos);
SDL_BlitSurface(value, NULL, screen, &valuePos);
}
/**
 * @brief controls the store mouse clicks.
 * @param[in] SDL_Event event the action made by the user.
  * @param[in] SDL_Surface* screen the screen to print.
  * @param[in] soundFX sfx the sounds that will be generated.
  * @param[in] SDL_Surface* screen the screen to print.
 * @return It returns 0 if back button is clicked or any number ordered by the store items starting from 1 or -1 if nothing is clicked.
 */
int storeClicks(SDL_Event event, buttons bu, soundFX sfx){
  //each new store item added you should add a new condition that returns a number.
  if(((event.button.x <= (bu.backbutPos.x + bu.backbut->w)) && (event.button.x >= bu.backbutPos.x)) && ((event.button.y >= bu.backbutPos.y) && (event.button.y <= (bu.backbutPos.y + bu.backbut->h)))) {
    if(sfx.soundMuted == 0){
   Mix_PlayChannel(-1, sfx.butClick, 0);
   }
     return 0;
 }else{
   if(((event.button.x <= 165) && (event.button.x >= 18)) && ((event.button.y >= 141) && (event.button.y <= 192))) {
     if(sfx.soundMuted == 0){
    Mix_PlayChannel(-1, sfx.butClick, 0);
    }
      return 1;
  }else{
    if(((event.button.x <= 324) && (event.button.x >= 183)) && ((event.button.y >= 141) && (event.button.y <= 192))) {
      if(sfx.soundMuted == 0){
     Mix_PlayChannel(-1, sfx.butClick, 0);
     }
       return 2;
   }else{
     if(((event.button.x <= 488) && (event.button.x >= 348)) && ((event.button.y >= 141) && (event.button.y <= 192))) {
       if(sfx.soundMuted == 0){
      Mix_PlayChannel(-1, sfx.butClick, 0);
      }
        return 3;
    }else{
      if(((event.button.x <= 165) && (event.button.x >= 18)) && ((event.button.y >= 201) && (event.button.y <= 240))) {
        if(sfx.soundMuted == 0){
       Mix_PlayChannel(-1, sfx.butClick, 0);
       }
         return 4;
     }else{
       if(((event.button.x <= 324) && (event.button.x >= 183)) && ((event.button.y >= 201) && (event.button.y <= 240))) {
         if(sfx.soundMuted == 0){
        Mix_PlayChannel(-1, sfx.butClick, 0);
        }
          return 5;
      }else{
        if(((event.button.x <= 488) && (event.button.x >= 348)) && ((event.button.y >= 201) && (event.button.y <= 240))) {
          if(sfx.soundMuted == 0){
         Mix_PlayChannel(-1, sfx.butClick, 0);
         }
           return 6;
       }
      }
     }
    }
   }
  }
 }
 return -1;
}
/**
 * @brief This function manages all items that were bought and manages tics when user buy something.
  * @param[in] int itemSelected the item of the store that was pressed and selected by user.
  * @param[in] SDL_Surface * screen the screen pointer to print on the dialog box.
 * @return Returns 1 if successfully applying changes otherwise 0.
 */
int buyingManger(int itemSelected, SDL_Surface * screen){
  int counter, items[10];
  int buffer;
  FILE *f = NULL;
  //This if-switch-like structure is just to verify if a theme is already applied to not reapply it again.
  f = fopen("backup/general.toe", "rb");
  char name[256];
  int x;
  fread(&name, sizeof(char)*256,1, f);
  if(strcmp(name, "Resources/themes/greeness.jpg") == 0){
      x = 1;
  }else{
    if(strcmp(name, "Resources/themes/black-metal.jpg") == 0){
      x = 2;
    }else{
      if(strcmp(name, "Resources/themes/sea.jpg") == 0){
        x = 3;
      }else{
        if(strcmp(name, "Resources/themes/woody.jpg") == 0){
          x = 4;
        }else{
          if(strcmp(name, "Resources/themes/cubic.jpg") == 0){
            x = 5;
          }else{
            if(strcmp(name, "Resources/themes/ciramic.jpg") == 0){
              x = 6;
            }
          }
        }
      }
    }
  }
  fclose(f);
  SDL_Surface * not_enough = IMG_Load("Resources/notenoughmoney.png");
  SDL_Rect rest;
  rest.x = 100;
  rest.y = 150;
  rest.h = not_enough->h;
  rest.w = not_enough->w;

  if((itemSelected == 1) && (itemSelected != x)){
    f = fopen("backup/general.toe", "rb");
    char themeName[256];
    fread(&themeName, sizeof(char)*256,1, f);
    if(strcmp(themeName, "Resources/themes/greeness.jpg") != 0){
      fclose(f);
      f = fopen("backup/general.toe", "wb");
      strcpy(themeName, "Resources/themes/greeness.jpg");
      fwrite(&themeName, 1, sizeof(char)*256, f);
      fclose(f);
    }else{
      fclose(f);
      return 0;
    }
    return 1;
  }else{
    f = fopen("backup/items.toe", "rb");
    //the stop condition in the loop bellow should increment as the number of items increase.
    for(counter = 0; counter < 6; counter++){
      fread(&buffer, sizeof(int), 1, f);
      items[counter] = buffer;
    }
    fclose(f);
    if((itemSelected == 2) && (itemSelected != x)){ // the x varaible is for checking that theme is not already applied
      if(items[1] == 0){
          f = fopen("backup/tics.toe", "rb");
          fread(&buffer, sizeof(int), 1, f);
        if((buffer >= 90) && (buffer > 0)){
          buffer -= 90;
          fclose(f);
          f = fopen("backup/tics.toe", "wb");
          fwrite(&buffer, 1,sizeof(int), f);
          fclose(f);
          //reading from items.toe
          f = fopen("backup/items.toe", "rb");
          for(counter = 0; counter < 6; counter++){
            fread(&buffer, sizeof(int), 1, f);
            items[counter] = buffer;
          }
          items[itemSelected-1] = 1;
          fclose(f);
          //writing to items.toe
          f = fopen("backup/items.toe", "wb");
          for(counter = 0; counter < 6; counter++){
            buffer = items[counter];
            fwrite(&buffer, 1, sizeof(int), f);
          }
          fclose(f);
        }else{

  				SDL_BlitSurface(not_enough, NULL, screen, &rest);
  				SDL_Flip(screen);
  				SDL_FreeSurface(not_enough);
          SDL_Delay(2000);
          fclose(f);
          return 0;
        }
        f = fopen("backup/general.toe", "wb");
        char themeName[256];
        strcpy(themeName, "Resources/themes/black-metal.jpg");
        fwrite(&themeName, 1, sizeof(char)*256, f);
        fclose(f);
    }else{
      //if item already bought then choose it
      f = fopen("backup/general.toe", "wb");
      char themeName[256];
      strcpy(themeName, "Resources/themes/black-metal.jpg");
      fwrite(&themeName, 1, sizeof(char)*256, f);
      fclose(f);
    }
    return 1;
  }else{
    if((itemSelected == 3) && (itemSelected != x)){
      if(items[2] == 0){
          f = fopen("backup/tics.toe", "rb");
          fread(&buffer, sizeof(int), 1, f);
        if((buffer >= 150) && (buffer > 0)){
          buffer -= 150;
          fclose(f);
          f = fopen("backup/tics.toe", "wb");
          fwrite(&buffer, 1,sizeof(int), f);
          fclose(f);
          //reading from items.toe
          f = fopen("backup/items.toe", "rb");
          //the stop condition in the loop bellow should increment as the number of items increase.
          for(counter = 0; counter < 6; counter++){
            fread(&buffer, sizeof(int), 1, f);
            items[counter] = buffer;
          }
          items[itemSelected-1] = 1;
          fclose(f);
          //writing to items.toe
          f = fopen("backup/items.toe", "wb");
          //the stop condition in the loop bellow should increment as the number of items increase.
          for(counter = 0; counter < 6; counter++){
            buffer = items[counter];
            fwrite(&buffer, 1, sizeof(int), f);
          }
          fclose(f);
        }else{

  				SDL_BlitSurface(not_enough, NULL, screen, &rest);
  				SDL_Flip(screen);
  				SDL_FreeSurface(not_enough);
          SDL_Delay(2000);
          fclose(f);
          return 0;
        }
        f = fopen("backup/general.toe", "wb");
        char themeName[256];
        strcpy(themeName, "Resources/themes/sea.jpg");
        fwrite(&themeName, 1, sizeof(char)*256, f);
        fclose(f);
      }else{
        //if item already bought then choose it
        f = fopen("backup/general.toe", "wb");
        char themeName[256];
        strcpy(themeName, "Resources/themes/sea.jpg");
        fwrite(&themeName, 1, sizeof(char)*256, f);
        fclose(f);
      }
      return 1;
  }else{
    if((itemSelected == 4) && (itemSelected != x)){
      if(items[3] == 0){
          f = fopen("backup/tics.toe", "rb");
          fread(&buffer, sizeof(int), 1, f);
        if((buffer >= 220) && (buffer > 0)){
          buffer -= 220;
          fclose(f);
          f = fopen("backup/tics.toe", "wb");
          fwrite(&buffer, 1,sizeof(int), f);
          fclose(f);
          //reading from items.toe
          f = fopen("backup/items.toe", "rb");
          //the stop condition in the loop bellow should increment as the number of items increase.
          for(counter = 0; counter < 6; counter++){
            fread(&buffer, sizeof(int), 1, f);
            items[counter] = buffer;
          }
          items[itemSelected-1] = 1;
          fclose(f);
          //writing to items.toe
          f = fopen("backup/items.toe", "wb");
          for(counter = 0; counter < 6; counter++){
            buffer = items[counter];
            fwrite(&buffer, 1, sizeof(int), f);
          }
          fclose(f);
        }else{

  				SDL_BlitSurface(not_enough, NULL, screen, &rest);
  				SDL_Flip(screen);
  				SDL_FreeSurface(not_enough);
          SDL_Delay(2000);
          fclose(f);
          return 0;
        }
        f = fopen("backup/general.toe", "wb");
        char themeName[256];
        strcpy(themeName, "Resources/themes/woody.jpg");
        fwrite(&themeName, 1, sizeof(char)*256, f);
        fclose(f);
    }else{
      //if item already bought then choose it
      f = fopen("backup/general.toe", "wb");
      char themeName[256];
      strcpy(themeName, "Resources/themes/woody.jpg");
      fwrite(&themeName, 1, sizeof(char)*256, f);
      fclose(f);
    }
    return 1;
  }else{
    if((itemSelected == 5) && (itemSelected != x)){
      if(items[4] == 0){
          f = fopen("backup/tics.toe", "rb");
          fread(&buffer, sizeof(int), 1, f);
        if((buffer >= 250) && (buffer > 0)){
          buffer -= 250;
          fclose(f);
          f = fopen("backup/tics.toe", "wb");
          fwrite(&buffer, 1,sizeof(int), f);
          fclose(f);
          //reading from items.toe
          f = fopen("backup/items.toe", "rb");
          //the stop condition in the loop bellow should increment as the number of items increase.
          for(counter = 0; counter < 6; counter++){
            fread(&buffer, sizeof(int), 1, f);
            items[counter] = buffer;
          }
          items[itemSelected-1] = 1;
          fclose(f);
          //writing to items.toe
          f = fopen("backup/items.toe", "wb");
          for(counter = 0; counter < 6; counter++){
            buffer = items[counter];
            fwrite(&buffer, 1, sizeof(int), f);
          }
          fclose(f);
        }else{

  				SDL_BlitSurface(not_enough, NULL, screen, &rest);
  				SDL_Flip(screen);
  				SDL_FreeSurface(not_enough);
          SDL_Delay(2000);
          fclose(f);
          return 0;
        }
        f = fopen("backup/general.toe", "wb");
        char themeName[256];
        strcpy(themeName, "Resources/themes/cubic.jpg");
        fwrite(&themeName, 1, sizeof(char)*256, f);
        fclose(f);
    }else{
      //if item already bought then choose it
      f = fopen("backup/general.toe", "wb");
      char themeName[256];
      strcpy(themeName, "Resources/themes/cubic.jpg");
      fwrite(&themeName, 1, sizeof(char)*256, f);
      fclose(f);
    }
    return 1;
  }else{
    if((itemSelected == 6) && (itemSelected != x)){
      if(items[5] == 0){
          f = fopen("backup/tics.toe", "rb");
          fread(&buffer, sizeof(int), 1, f);
        if((buffer >= 290) && (buffer > 0)){
          buffer -= 290;
          fclose(f);
          f = fopen("backup/tics.toe", "wb");
          fwrite(&buffer, 1,sizeof(int), f);
          fclose(f);
          //reading from items.toe
          f = fopen("backup/items.toe", "rb");
          //the stop condition in the loop bellow should increment as the number of items increase.
          for(counter = 0; counter < 6; counter++){
            fread(&buffer, sizeof(int), 1, f);
            items[counter] = buffer;
          }
          items[itemSelected-1] = 1;
          fclose(f);
          //writing to items.toe
          f = fopen("backup/items.toe", "wb");
          for(counter = 0; counter < 6; counter++){
            buffer = items[counter];
            fwrite(&buffer, 1, sizeof(int), f);
          }
          fclose(f);
        }else{

  				SDL_BlitSurface(not_enough, NULL, screen, &rest);
  				SDL_Flip(screen);
  				SDL_FreeSurface(not_enough);
          SDL_Delay(2000);
          fclose(f);
          return 0;
        }
        f = fopen("backup/general.toe", "wb");
        char themeName[256];
        strcpy(themeName, "Resources/themes/ceramic.jpg");
        fwrite(&themeName, 1, sizeof(char)*256, f);
        fclose(f);
    }else{
      //if item already bought then choose it
      f = fopen("backup/general.toe", "wb");
      char themeName[256];
      strcpy(themeName, "Resources/themes/ceramic.jpg");
      fwrite(&themeName, 1, sizeof(char)*256, f);
      fclose(f);
    }
    return 1;
  }
  }
  }
}
  }
  }
  if(itemSelected == x){
    SDL_Surface * already_chosen = IMG_Load("Resources/alreadychosen.png");
    SDL_Rect Pos;
    Pos.x = 100;
    Pos.y = 150;
    Pos.h = already_chosen->h;
    Pos.w = already_chosen->w;
    SDL_BlitSurface(already_chosen, NULL, screen, &Pos);
    SDL_Flip(screen);
    SDL_FreeSurface(already_chosen);
    SDL_Delay(1500);
  }
}
