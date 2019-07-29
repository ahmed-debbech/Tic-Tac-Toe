/**
 * @file main.c
 * @author Ahmed Debbech
 * @brief The main entry point to the program, all the function calls are here.
 */
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include <string.h>
#include "graphics.h"
#include "store.h"
#include "core.h"
int main(int argc, char **argv){
//core initializations
	char m[3][3]; //main game table containing Xs and Os
	int td[3][3]; //defence table
	int ta[3][3]; // attack table
	computerEnteries ce;
//graphics initializations
SDL_Surface *screen;
Mix_Music * music;
SDL_Event event;
menu mc;
int scoreComputer=0, scorePlayer=0, whichMode = 0;
int scorePlayer1 = 0, scorePlayer2=0;
int played_once = 0;
playgameScreen pgs;
about ab;
help hel;
picker p;
menuPlayGame mpg;
buttons bu;
control c;
soundFX sfx;
tics t;
store s;
points poi;
poi.user_points = 0;
// screen initialization
if(SDL_Init(SDL_INIT_VIDEO)!=0){
printf("unable to initialize SDL:%s \n",SDL_GetError());
	return 1;
}
SDL_Surface * icon = IMG_Load("Resources/icon.png");
SDL_WM_SetIcon(icon, NULL);
screen = SDL_SetVideoMode(500,490,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1){
	printf("No sounds %s\n",Mix_GetError());
        return 1;
}
SDL_WM_SetCaption("Tic Tac Toe v2.3", NULL);
//flags declaration and initialization
int menuNotOver = 1, blitCheck = 0, choice;
int passToGame = 0, click, gameNotFinished = 1;
int game_isnot_going = 0;
 c.soundMuted = 0;
 //initializations
 creating_files();
mc = initOffMenu();
sfx = initSounds();
bu = initButtons();
s = initStore();
SDL_BlitSurface (mc.splash, NULL, screen, &mc.splashPos);
SDL_Flip(screen);
int empty = 0;
SDL_Delay(2500);
while (empty == 0){
	if(SDL_PollEvent(&event) == 1){
		empty = 0;
	}else{
		if(SDL_PollEvent(&event) == 0){
			empty = 1;
		}
	}
}  //empty the event queue
while (game_isnot_going == 0){
	//official menu
while(menuNotOver == 1){
	if(blitCheck == 0){
		showOffMenu(mc, screen,c);
		SDL_Flip(screen);
  }
	SDL_WaitEvent(&event);
      switch(event.type){
        case SDL_QUIT:
          game_isnot_going = 1;
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
 // manipulating choices comming from menu
 switch (choice) {
 	case 1:
	while(SDL_PollEvent(&event)){
	if(event.type == SDL_QUIT){
		game_isnot_going = 1;
	}else{
		//playgame menu screen
		if(passToGame == 0){
   mpg = initMenuPlay();
	 if(blitCheck == 0){
	   showMenuPlay(mpg,screen,bu);
	   SDL_Flip(screen);
	 }
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
		  click = menuPlayClicks(event, bu,mpg,c,sfx);
		 if(click == 0){
			 //this initialization just to let back to the menu
			 choice = 0;
			 menuNotOver = 1;
			 blitCheck = 0;
		 }else{
			 if(click == -1){
				 passToGame = 0;
				 game_isnot_going = 1;
			 }else{
			 passToGame = 1;
		   }
		 }
}
 }

}else{
	//pass to game play
	//picker menu screen
	int userInput, won=0;
	int winner = 0;
	char whatComputerChose = 'n';
	if(passToGame == 1){
		//pass to computer mode
		if(click == 1){
			if(initPickScreen(&p) == 1){
				while (SDL_PollEvent(&event) != 0);
			   	p = getPick(screen, event,p,sfx, c);
				whichMode = 0;
				if(played_once == 1){
					showScore(winner, scoreComputer, scorePlayer, screen,pgs, whichMode);
				}
				if(p.pick == 'n'){
				passToGame = 0; // to be back to the playgame menu
			}else{
        if(p.pick == 'x'){
					won=0;
					winner = 0;
					played_once = 1;
					whatComputerChose = 'o';
					init(m);
					initDeffTable(td);
					initAttTable(ta);
					pgs = initGamePlay();
					SDL_BlitSurface(pgs.splashCharIndicatorX,NULL, screen, &pgs.splashIndicatorPos);
					SDL_Flip(screen);
					SDL_Delay(750);
					showGamePlay(pgs, screen);
					showScore(winner, scoreComputer, scorePlayer, screen,pgs, whichMode);
					printPoints(poi, screen);
					printTics(t,screen);
					SDL_Flip(screen);
					while (SDL_PollEvent(&event) != 0);  //empty the event queue before start to not crash the game with to many events from the splash screen
					//actual game loop
					do{
				  	do{
								SDL_WaitEvent(&event);
					  		userInput = player(m, screen, pgs, p.pick,event,sfx,c);
				    }while(userInput == 0);
						checkwin(m,&winner,whatComputerChose,&won, screen, pgs);
						SDL_Delay(250);
						while (SDL_PollEvent(&event) != 0);  //empty the event queue
						if((won != 1) && (checkfin(m) != 1) && ((userInput != -1) && (userInput != 3))){
				     computerBrain(m,&ce.xc, &ce.yc, td, ta,whatComputerChose);
				     printOnTable(ce,m,screen,pgs,p.pick);
				     checkwin(m,&winner,whatComputerChose,&won, screen, pgs);
					 }
			 }while(((checkfin(m) == 0) && (won == 0)) && ((userInput != -1) && (userInput != 3)));
       SDL_Delay(1000);
			 if((won == 1) && ((userInput != -1) && (userInput != 3))){
					 manageScore (winner, &scoreComputer, &scorePlayer);
					 if(winner == 2){
					  if(c.soundMuted == 0){
			       Mix_PlayChannel(-1, sfx.winning, 0);
			      }
					}else{
						if(c.soundMuted == 0){
			       Mix_PlayChannel(-1, sfx.lose, 0);
			      }
					}
					 showScore(winner, scoreComputer, scorePlayer, screen,pgs,whichMode);
					 managePoints(&poi, winner, scoreComputer, scorePlayer,screen);
					 t = manageTics(winner);
					 	while (SDL_PollEvent(&event) != 0);
					 SDL_Flip(screen);
			 }else{
				 if(userInput == -1){
			   	 game_isnot_going = 1; // quit the game
			   }else{
					 if(userInput == 3){
						 passToGame = 0; // when pressing back button to back to menu
					 }
				 }
			 }
				}else{
					if(p.pick == 'o'){
						won=0;
						winner = 0;
						played_once = 1;
						whatComputerChose = 'x';
						init(m);
						initDeffTable(td);
						initAttTable(ta);
						pgs = initGamePlay();
						SDL_BlitSurface(pgs.splashCharIndicatorO,NULL, screen, &pgs.splashIndicatorPos);
						SDL_Flip(screen);
						SDL_Delay(750);
						showGamePlay(pgs, screen);
						showScore(winner, scoreComputer, scorePlayer, screen,pgs, whichMode);
						printPoints(poi, screen);
						printTics(t,screen);
						SDL_Flip(screen);
						while (SDL_PollEvent(&event) != 0);  //empty the event queue
						//actual game loop
						do{
							SDL_Delay(250);
							while (SDL_PollEvent(&event) != 0);  //empty the event queue
							computerBrain(m,&ce.xc, &ce.yc, td, ta,whatComputerChose);
							printOnTable(ce,m,screen,pgs,p.pick);
							checkwin(m,&winner,whatComputerChose,&won, screen, pgs);
							if((won != 1) && (checkfin(m) != 1) && ((userInput != -1) && (userInput != 3))){
								do{
									SDL_WaitEvent(&event);
							  	userInput = player(m, screen, pgs, p.pick, event,sfx, c);
						    }while(userInput == 0);
					     checkwin(m,&winner,whatComputerChose,&won, screen, pgs);
						 }
				 }while(((checkfin(m) == 0) && (won == 0)) && ((userInput != -1) && (userInput != 3)));
	       SDL_Delay(1000);
				 if((won == 1) && ((userInput != -1) && (userInput != 3))){
						 manageScore (winner, &scoreComputer, &scorePlayer);
						 if(winner == 2){
						 if(c.soundMuted == 0){
							Mix_PlayChannel(-1, sfx.winning, 0);
						 }
					 }else{
						 if(c.soundMuted == 0){
							Mix_PlayChannel(-1, sfx.lose, 0);
						 }
					 }
						 showScore(winner, scoreComputer, scorePlayer, screen,pgs, whichMode);
						 managePoints(&poi, winner, scoreComputer, scorePlayer,screen);
						 t = manageTics(winner);
						 while (SDL_PollEvent(&event) != 0);
						 SDL_Flip(screen);
				 }else{
					 if(userInput == -1){
				   	 game_isnot_going = 1; // quit the game
				   }else{
						 if(userInput == 3){
							 passToGame = 0; // when pressing back button to back to menu

						 }
					 }
				 }
					}
				}
			}
			}

		}else{
			//pass to friend mode
			if(click == 2){
				won=0;
				winner = 0;
				played_once = 1;
				init(m);
				pgs = initGamePlay();
				showGamePlay(pgs, screen);
				whichMode = 1; // this variable is set to 1 to say it is friend mode
				showScore(winner, scorePlayer1, scorePlayer2, screen,pgs, whichMode);
				SDL_Flip(screen);
				//actual game loop
				do{
					do{
						SDL_WaitEvent(&event);
						userInput = player(m, screen, pgs, 'x', event,sfx,c);
					}while(userInput == 0);
					checkwin(m,&winner,'x',&won, screen, pgs);
					if((won != 1) && (checkfin(m) != 1) && ((userInput != -1) && (userInput != 3))){
						do{
							SDL_WaitEvent(&event);
							userInput = player(m, screen, pgs, 'o',event,sfx,c);
						}while(userInput == 0);
					 checkwin(m,&winner,'x',&won, screen, pgs);
				 }
		 }while(((checkfin(m) == 0) && (won == 0)) && ((userInput != -1) && (userInput != 3)));
		 SDL_Delay(1000);
		 if((won == 1) && ((userInput != -1) && (userInput != 3))){
				 manageScore (winner, &scorePlayer1, &scorePlayer2);
					if(c.soundMuted == 0){
					 Mix_PlayChannel(-1, sfx.winning, 0);
					}
				 showScore(winner, scorePlayer1, scorePlayer2, screen,pgs, whichMode);
				 SDL_Flip(screen);
		 }else{
			 if(userInput == -1){
				 game_isnot_going = 1; // quit the game
			 }else{
				 if(userInput == 3){
					 passToGame = 0; // when pressing back button to back to menu

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
	 case 2:
	 SDL_WaitEvent(&event);
	 if(event.type == SDL_QUIT){
		 game_isnot_going = 1;
	 }else{
		if(blitCheck == 0){
	  showStore(s,screen,bu);
		SDL_Flip(screen);
		}
		if(event.type == SDL_MOUSEBUTTONDOWN){
			int o = -1;
			o = storeClicks(event, bu,sfx,c);
			//if back button was pressed
			if(o == 0){
				choice = 0;
				menuNotOver = 1;
			}else{
				//if any of the items was pressed
				if(buyingManger(o,screen) == 1){
						//the image that contains restart instruction to excute the new changes
						SDL_Surface * restart = IMG_Load("Resources/restart.png");
						SDL_Rect rest;
						rest.x = 100;
						rest.y = 150;
						rest.h = restart->h;
						rest.w = restart->w;
						SDL_BlitSurface(restart, NULL, screen, &rest);
						SDL_Flip(screen);
						SDL_FreeSurface(restart);
						SDL_Delay(5000);
						game_isnot_going = 1;
			   }
			}
		}
}
	 break;
	 case 3:
	 SDL_WaitEvent(&event);
 	if(event.type == SDL_QUIT){
 		game_isnot_going = 1;
 	}else{
     hel = initHelp();
		 if(blitCheck == 0){
		 showHelp(hel,screen,bu);
		 SDL_Flip(screen);
		 }
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
			 if(helpClicks(event, bu,sfx,c) == 1){
				 choice = 0;
				 menuNotOver = 1;
			 }
		 }
	 }
}

 	 break;
	 case 4:
	 SDL_WaitEvent(&event);
	 if(event.type == SDL_QUIT){
		 game_isnot_going = 1;
	 }else{
		 ab = initAbout();
		if(blitCheck == 0){
		showAbout(ab,screen,bu);
		SDL_Flip(screen);
		}
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
			if(aboutClicks(event, bu,sfx, c) == 1){
				choice = 0;
				menuNotOver = 1;
			}
		}
	}

}
 	 break;
	 //power button processing
	 case 6:
	 game_isnot_going = 1;
 	 break;
 }
}
//end game loop
SDL_FreeSurface(screen);
Mix_FreeMusic(music);
SDL_Quit();
return 0;
}
