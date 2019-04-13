#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include <string.h>
#include "graphics.h"
int main(){
SDL_Surface *screen;
Mix_Music * music;
SDL_Event event;
menu mc;
about ab;
help hel;
menuPlayGame mpg;
buttons bu;
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
	//official menu
while(menuNotOver == 1){
	if(blitCheck == 0){
	showOffMenu(mc, screen,c);
	SDL_Flip(screen);
  }
SDL_WaitEvent(&event);
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
		          choice = menuClicks(mc,screen, event, &c,&sfx);
           if(choice == 5){
						 menuNotOver = 1;
					 }else{
							menuNotOver = 0;
							blitCheck = 0;
						}
						break;
      }
   }
 // manipulating choices
 bu = initButtons();
 switch (choice) {
 	case 1:
	SDL_WaitEvent(&event);
	if(event.type == SDL_QUIT){
		done = 1;
	}else{
   mpg = initMenuPlay();
	 if(blitCheck == 0){
	   showMenuPlay(mpg,screen,bu);
	   SDL_Flip(screen);
	 }
	 SDL_WaitEvent(&event);
 if(event.type == SDL_MOUSEMOTION){
	 if(menuPlayMotion(bu, mpg,screen, event,c,sfx) == 1){
		 blitCheck = 1;
		 SDL_Flip(screen);
	 }else{
		 SDL_Flip(screen);
		 blitCheck = 0;
	 }
 }else{
	 if(event.type == SDL_MOUSEBUTTONDOWN){
		 if(menuPlayClicks(event, bu,mpg,c,sfx) == 0){
			 //this initialization just to let back to the menu
			 choice = 0;
			 menuNotOver = 1;
			 blitCheck = 0;
		 }
	 }
 }
	}
	 break;
	 case 2:
	 SDL_PollEvent(&event) ;
 	if(event.type == SDL_QUIT){
 		done = 1;
 	}else{
     hel = initHelp();
		 if(blitCheck == 0){
		 showHelp(hel,screen,bu);
		 SDL_Flip(screen);
		 }
		 SDL_PollEvent(&event);
		 if(event.type == SDL_MOUSEMOTION){
		 if(helpMotion(bu, hel,screen, event) == 1){
		   blitCheck = 1;
		   SDL_Flip(screen);
		 }else{
		   SDL_Flip(screen);
		   blitCheck = 0;
		 }
	 }else{
		 if(event.type == SDL_MOUSEBUTTONDOWN){
			 if(helpClicks(event, bu) == 1){
				 choice = 0;
				 menuNotOver = 1;
			 }
		 }
	 }
}
 	 break;
	 case 3:
	 SDL_PollEvent(&event) ;
	 if(event.type == SDL_QUIT){
		 done = 1;
	 }else{
		 ab = initAbout();
		if(blitCheck == 0){
		showAbout(ab,screen,bu);
		SDL_Flip(screen);
		}
		SDL_PollEvent(&event);
		if(event.type == SDL_MOUSEMOTION){
		if(aboutMotion(bu, ab,screen, event) == 1){
			blitCheck = 1;
			SDL_Flip(screen);
		}else{
			SDL_Flip(screen);
			blitCheck = 0;
		}
	}else{
		if(event.type == SDL_MOUSEBUTTONDOWN){
			if(aboutClicks(event, bu) == 1){
				choice = 0;
				menuNotOver = 1;
			}
		}
	}
}
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
