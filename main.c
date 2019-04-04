#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include <string.h>
#include "graphics.h"
#include "core.h"
int main(){

SDL_Surface *screen;
Mix_Music * music;
SDL_Event event;
menu mc;
control c;
soundFX sfx;
if(SDL_Init(SDL_INIT_VIDEO)!=0){
printf("unable to initializeSDL:%s \n",SDL_GetError());
	return 1;
}

screen = SDL_SetVideoMode(500,490,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1){
	printf("No sounds %s\n",Mix_GetError());
        return 1;
}
SDL_WM_SetCaption("Tic Tac Toe", NULL);
int done = 0, menuNotOver = 1, blitCheck = 0, choice;
 c.soundMuted = 0;
mc = initOffMenu();
sfx = initSounds();
SDL_BlitSurface (mc.splash, NULL, screen, &mc.splashPos);
SDL_Flip(screen);
SDL_Delay(3000);
//game loop
while (done == 0){
while(menuNotOver == 1){
	if(blitCheck == 0){
	showOffMenu(mc, screen);
	SDL_Flip(screen);
  }
 while(SDL_PollEvent(&event) == 1){
      switch(event.type){
        case SDL_QUIT:
          done = 1;
					menuNotOver = 0;
          break;
				case SDL_MOUSEMOTION:
	          if(menuMotion(mc,screen, event, c, sfx) == 1){
							blitCheck = 1;
						}else{
							blitCheck = 0;
						}
	        break;
				case SDL_MOUSEBUTTONDOWN:
		          choice = menuClicks(mc,screen, event, c,&sfx);
							if (choice == 5) {
						      menuNotOver =1 ;
							}else{
							menuNotOver = 0;
						}
		        break;
      }
   }
 }
 switch (choice) {
 	case 1:
	 break;
	 case 2:
 	 break;
	 case 3:
 	 break;
	 case 4:
	 done = 1;
 	 break;
 }
}
//end game loop
SDL_FreeSurface(screen);
Mix_FreeMusic(music);
SDL_Quit();
return 0;
}
