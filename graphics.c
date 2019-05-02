#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "graphics.h"

buttons initButtons(){
  buttons bu;
  bu.backbut = IMG_Load("Resources/back.png");
  bu.backbut2 = IMG_Load("Resources/back2.png");
  if((bu.backbut == NULL) || (bu.backbut2 == NULL)){
    printf("couldn't load some images\n");
  }else{
    bu.backbutPos.x = 10; bu.backbutPos.y = 455;
    bu.backbutPos.h = bu.backbut->h ;bu.backbutPos.w = bu.backbut->w;
  }
  return bu;
}
soundFX initSounds(){
  soundFX sfx;
  sfx.butHover = Mix_LoadWAV("Resources/hover.wav");
  sfx.butClick = Mix_LoadWAV("Resources/click.wav");
  return sfx;
}
menu initOffMenu(){
  menu m;
  m.splash = IMG_Load("Resources/init.png");
  m.menuBack = IMG_Load("Resources/menuback.png");
  m.playbut = IMG_Load("Resources/playbut.png");
  m.playbut2 = IMG_Load("Resources/playbut2.png");
  m.helpbut = IMG_Load("Resources/helpbut.png");
  m.helpbut2 = IMG_Load("Resources/helpbut2.png");
  m.aboutbut = IMG_Load("Resources/aboutbut.png");
  m.aboutbut2 = IMG_Load("Resources/aboutbut2.png");
  m.soundbut = IMG_Load("Resources/sound.png");
  m.soundbut2 = IMG_Load("Resources/sound2.png");
  m.powerbut = IMG_Load("Resources/power.png");
  //splash
  m.splashPos.x = 0; m.splashPos.y = 0;
  m.splashPos.h = m.splash->h;  m.splashPos.w = m.splash->w;
  //menuback
  m.menuBackPos.x = 0; m.menuBackPos.y = 0;
  m.menuBackPos.h = m.menuBack->h; m.menuBackPos.w = m.menuBack->w;
  //play
  m.playbutPos.x = 150; m.playbutPos.y = 150;
  m.playbutPos.h = m.playbut->h; m.playbutPos.w = m.playbut->w;
  //help
  m.helpbutPos.x = 150; m.helpbutPos.y = 250;
  m.helpbutPos.h = m.helpbut->h; m.helpbutPos.w = m.helpbut->w;
  //about
  m.aboutbutPos.x = 150; m.aboutbutPos.y = 350;
  m.aboutbutPos.h = m.aboutbut->h; m.aboutbutPos.w = m.aboutbut->w;
  //sound
  m.soundbutPos.x = 5; m.soundbutPos.y = 450;
  m.soundbutPos.h = m.soundbut->h; m.soundbutPos.w = m.soundbut->w;
  //quit
  m.powerbutPos.x = 450; m.powerbutPos.y = 450;
  m.powerbutPos.h = m.powerbut->h; m.powerbutPos.w = m.powerbut->w;
  return m;
}
void showOffMenu(menu mc, SDL_Surface * screen, control c){
  SDL_BlitSurface (mc.menuBack, NULL, screen, &mc.menuBackPos);
 SDL_BlitSurface (mc.playbut, NULL, screen, &mc.playbutPos);
 SDL_BlitSurface (mc.helpbut, NULL, screen, &mc.helpbutPos);
 SDL_BlitSurface (mc.aboutbut, NULL, screen, &mc.aboutbutPos);
 if(c.soundMuted == 0){
 SDL_BlitSurface (mc.soundbut, NULL, screen, &mc.soundbutPos);
}else{
  SDL_BlitSurface (mc.soundbut2, NULL, screen, &mc.soundbutPos);

}
 SDL_BlitSurface (mc.powerbut, NULL, screen, &mc.powerbutPos);
}
int menuMotion(menu mc, SDL_Surface * screen, SDL_Event event, control c, soundFX sfx){
  int y =0;
  static int played = 0;
    if(((event.motion.x <= (mc.playbutPos.x + mc.playbutPos.w)) && (event.motion.x >= mc.playbutPos.x)) && ((event.motion.y >= mc.playbutPos.y) && (event.motion.y <= (mc.playbutPos.y + mc.playbutPos.h)))) {
      if(c.soundMuted == 0){
      if(played == 0){
      Mix_PlayChannel(-1, sfx.butHover, 0);
      played = 1;
      }
      }
  mc.playbutPos.h = mc.playbut->h;
  mc.playbutPos.w = mc.playbut->w;
    SDL_BlitSurface(mc.playbut2,NULL,screen,&mc.playbutPos);
    SDL_Flip(screen);
  	y=1;
  }else{
    if(((event.motion.x <= (mc.helpbutPos.x + mc.helpbutPos.w)) && (event.motion.x >= mc.helpbutPos.x)) && ((event.motion.y >= mc.helpbutPos.y) && (event.motion.y <= (mc.helpbutPos.y + mc.helpbutPos.h)))) {
      if(c.soundMuted == 0){
      if(played == 0){
      Mix_PlayChannel(-1, sfx.butHover, 0);
      played = 1;
      }
      }
  mc.helpbutPos.h = mc.helpbut->h;
  mc.helpbutPos.w = mc.helpbut->w;
    SDL_BlitSurface(mc.helpbut2,NULL,screen,&mc.helpbutPos);
    SDL_Flip(screen);
  	y=1;
  }else{
    if(((event.motion.x <= (mc.aboutbutPos.x + mc.aboutbutPos.w)) && (event.motion.x >= mc.aboutbutPos.x)) && ((event.motion.y >= mc.aboutbutPos.y) && (event.motion.y <= (mc.aboutbutPos.y + mc.aboutbutPos.h)))) {
      if(c.soundMuted == 0){
      if(played == 0){
      Mix_PlayChannel(-1, sfx.butHover, 0);
      played = 1;
      }
      }
  mc.aboutbutPos.h = mc.aboutbut->h;
  mc.aboutbutPos.w = mc.aboutbut->w;
    SDL_BlitSurface(mc.aboutbut2,NULL,screen,&mc.aboutbutPos);
    SDL_Flip(screen);
   y=1;
 }else{
   played = 0;
 }
  }
  }
  return y;
}
int menuClicks (menu mc, SDL_Surface * screen, SDL_Event event, control *c, soundFX *sfx){
  int y = 0;
  if(((event.button.x <= (mc.playbutPos.x + mc.playbutPos.w)) && (event.button.x >= mc.playbutPos.x)) && ((event.button.y >= mc.playbutPos.y) && (event.button.y <= (mc.playbutPos.y + mc.playbutPos.h)))) {
   if(c->soundMuted == 0){
  Mix_PlayChannel(-1, sfx->butClick, 0);
  }
  y=1;
}else{
  if(((event.button.x <= (mc.helpbutPos.x + mc.helpbutPos.w)) && (event.button.x >= mc.helpbutPos.x)) && ((event.button.y >= mc.helpbutPos.y) && (event.button.y <= (mc.helpbutPos.y + mc.helpbutPos.h)))) {
   if(c->soundMuted == 0){
    Mix_PlayChannel(-1, sfx->butClick, 0);
  }
  y=2;
}else{
  if(((event.button.x <= (mc.aboutbutPos.x + mc.aboutbutPos.w)) && (event.button.x >= mc.aboutbutPos.x)) && ((event.button.y >= mc.aboutbutPos.y) && (event.button.y <= (mc.aboutbutPos.y + mc.aboutbutPos.h)))) {
   if(c->soundMuted == 0){
   Mix_PlayChannel(-1, sfx->butClick, 0);
 }
 y=3;
}else{
  if(((event.button.x <= (mc.powerbutPos.x + mc.powerbutPos.w)) && (event.button.x >= mc.powerbutPos.x)) && ((event.button.y >= mc.powerbutPos.y) && (event.button.y <= (mc.powerbutPos.y + mc.powerbutPos.h)))) {
    if(c->soundMuted == 0){
   Mix_PlayChannel(-1, sfx->butClick, 0);
 }
 y=4;
}else{
  if(((event.button.x <= (mc.soundbutPos.x + mc.soundbutPos.w)) && (event.button.x >= mc.soundbutPos.x)) && ((event.button.y >= mc.soundbutPos.y) && (event.button.y <= (mc.soundbutPos.y + mc.soundbutPos.h)))) {
   if(c->soundMuted == 0){
   c->soundMuted = 1;
   mc.soundbutPos.h = mc.soundbut->h;
   mc.soundbutPos.w = mc.soundbut->w;
   SDL_BlitSurface (mc.menuBack, NULL, screen, &mc.menuBackPos);
  SDL_BlitSurface (mc.playbut, NULL, screen, &mc.playbutPos);
  SDL_BlitSurface (mc.helpbut, NULL, screen, &mc.helpbutPos);
  SDL_BlitSurface (mc.aboutbut, NULL, screen, &mc.aboutbutPos);
  SDL_BlitSurface (mc.powerbut, NULL, screen, &mc.powerbutPos);
     SDL_BlitSurface(mc.soundbut2,NULL,screen,&mc.soundbutPos);
     SDL_Flip(screen);
   }else{
     c->soundMuted = 0;
     mc.soundbutPos.h = mc.soundbut->h;
     mc.soundbutPos.w = mc.soundbut->w;
     SDL_BlitSurface (mc.menuBack, NULL, screen, &mc.menuBackPos);
    SDL_BlitSurface (mc.playbut, NULL, screen, &mc.playbutPos);
    SDL_BlitSurface (mc.helpbut, NULL, screen, &mc.helpbutPos);
    SDL_BlitSurface (mc.aboutbut, NULL, screen, &mc.aboutbutPos);
    SDL_BlitSurface (mc.powerbut, NULL, screen, &mc.powerbutPos);
       SDL_BlitSurface(mc.soundbut2,NULL,screen,&mc.soundbutPos);
       SDL_Flip(screen);
   }
   y=5;
}else{
  y = 5;
}
}
     }
   }
 }
return y;
}
help initHelp(){
  help h;
  h.backhelp = IMG_Load("Resources/helpback.jpg");
  h.backPos.x = 0; h.backPos.y = 0;
  h.backPos.h = h.backhelp->h ; h.backPos.w = h.backhelp->w;
  return h;
}
void showHelp(help h, SDL_Surface* screen, buttons bu){
  SDL_BlitSurface(h.backhelp, NULL, screen, &h.backPos);
  SDL_BlitSurface(bu.backbut, NULL, screen, &bu.backbutPos);
}
int helpClicks(SDL_Event event, buttons bu){
  if(((event.button.x <= (bu.backbutPos.x + bu.backbut->w)) && (event.button.x >= bu.backbutPos.x)) && ((event.button.y >= bu.backbutPos.y) && (event.button.y <= (bu.backbutPos.y + bu.backbut->h)))) {
     return 1;
 }else{
   return 0 ;
 }
}
int helpMotion(buttons bu,help h, SDL_Surface * screen, SDL_Event event){
  int y =0;
    if(((event.motion.x <= (bu.backbutPos.x + bu.backbut->w)) && (event.motion.x >= bu.backbutPos.x)) && ((event.motion.y >= bu.backbutPos.y) && (event.motion.y <= (bu.backbutPos.y + bu.backbut->h)))) {

  bu.backbutPos.h = bu.backbut->h;
  bu.backbutPos.w = bu.backbut->w;
    SDL_BlitSurface(h.backhelp,NULL,screen,&h.backPos);
    SDL_BlitSurface(bu.backbut2,NULL,screen,&bu.backbutPos);
   y=1;
  }
  return y;
}
about initAbout(){
  about ab;
  ab.backabout = IMG_Load("Resources/aboutback.png");
  ab.backPos.x = 0; ab.backPos.y = 0;
  ab.backPos.h = ab.backabout->h ; ab.backPos.w = ab.backabout->w;
  return ab;
}
void showAbout(about a, SDL_Surface* screen, buttons bu){
  SDL_BlitSurface(a.backabout, NULL, screen, &a.backPos);
  SDL_BlitSurface(bu.backbut, NULL, screen, &bu.backbutPos);
}
int aboutMotion(buttons bu,about a,
  SDL_Surface * screen, SDL_Event event){
    int y =0;
      if(((event.motion.x <= (bu.backbutPos.x + bu.backbut->w)) && (event.motion.x >= bu.backbutPos.x)) && ((event.motion.y >= bu.backbutPos.y) && (event.motion.y <= (bu.backbutPos.y + bu.backbut->h)))) {

    bu.backbutPos.h = bu.backbut->h;
    bu.backbutPos.w = bu.backbut->w;
      SDL_BlitSurface(a.backabout,NULL,screen,&a.backPos);
      SDL_BlitSurface(bu.backbut2,NULL,screen,&bu.backbutPos);
     y=1;
    }
    return y;
  }
int aboutClicks(SDL_Event event, buttons bu){
  if(((event.button.x <= (bu.backbutPos.x + bu.backbut->w)) && (event.button.x >= bu.backbutPos.x)) && ((event.button.y >= bu.backbutPos.y) && (event.button.y <= (bu.backbutPos.y + bu.backbut->h)))) {
     return 1;
 }else{
   return 0 ;
 }
}
menuPlayGame initMenuPlay(){
  menuPlayGame mpg;
  mpg.back = IMG_Load("Resources/backplaymenu.jpg");
  mpg.computer = IMG_Load("Resources/computer.png");
  mpg.computer2 = IMG_Load("Resources/computer2.png");
  mpg.friend = IMG_Load("Resources/friend.png");
  mpg.friend2 = IMG_Load("Resources/friend2.png");
  if((mpg.back == NULL) || (mpg.computer == NULL) ||(mpg.computer2 == NULL)
|| (mpg.friend == NULL) || (mpg.friend2 == NULL)){
    printf("couldn't load images\n");
  }else{
    mpg.backPos.x = 0; mpg.backPos.y = 0;
    mpg.backPos.h = mpg.back->h; mpg.backPos.w = mpg.back->w;
    mpg.computerPos.x = 145; mpg.computerPos.y = 200;
    mpg.computerPos.h = mpg.computer->h; mpg.computerPos.w = mpg.computer->w;
    mpg.friendPos.x = 145; mpg.friendPos.y = 300;
    mpg.friendPos.h = mpg.friend->h; mpg.friendPos.w = mpg.friend->w;
  }
  return mpg;
}
void showMenuPlay(menuPlayGame mpg, SDL_Surface *screen, buttons bu){
  SDL_BlitSurface(mpg.back, NULL, screen, &mpg.backPos);
    SDL_BlitSurface(mpg.computer, NULL, screen, &mpg.computerPos);
    SDL_BlitSurface(mpg.friend, NULL, screen, &mpg.friendPos);
    SDL_BlitSurface(bu.backbut, NULL, screen, &bu.backbutPos);
}
int menuPlayMotion(buttons bu, menuPlayGame mpg, SDL_Surface * screen, SDL_Event event, control c, soundFX sfx){
static int played =0;
int y= 0;
  if(((event.motion.x <= (mpg.computerPos.x + mpg.computer->w)) && (event.motion.x >= mpg.computerPos.x)) && ((event.motion.y >= mpg.computerPos.y) && (event.motion.y <= (mpg.computerPos.y + mpg.computer->h)))) {
    if(c.soundMuted == 0){
    if(played == 0){
    Mix_PlayChannel(-1, sfx.butHover, 0);
    played = 1;
    }
    }
  mpg.computerPos.h = mpg.computer2->h;
  mpg.computerPos.w = mpg.computer2->w;
  SDL_BlitSurface(mpg.computer2,NULL,screen,&mpg.computerPos);
  SDL_Flip(screen);
  y=1;
  }else{
  if(((event.motion.x <= (mpg.friendPos.x + mpg.friend->w)) && (event.motion.x >= mpg.friendPos.x)) && ((event.motion.y >= mpg.friendPos.y) && (event.motion.y <= (mpg.friendPos.y + mpg.friend->h)))) {
    if(c.soundMuted == 0){
    if(played == 0){
    Mix_PlayChannel(-1, sfx.butHover, 0);
    played = 1;
    }
    }
  mpg.friendPos.h = mpg.friend2->h;
  mpg.friendPos.w = mpg.friend2->w;
  SDL_BlitSurface(mpg.friend2,NULL,screen,&mpg.friendPos);
  SDL_Flip(screen);
  y=1;
  }else{
    if(((event.motion.x <= (bu.backbutPos.x + bu.backbut->w)) && (event.motion.x >= bu.backbutPos.x)) && ((event.motion.y >= bu.backbutPos.y) && (event.motion.y <= (bu.backbutPos.y + bu.backbut->h)))) {
      if(c.soundMuted == 0){
      if(played == 0){
      Mix_PlayChannel(-1, sfx.butHover, 0);
      played = 1;
      }
    }
    bu.backbutPos.h = bu.backbut2->h;
    bu.backbutPos.w = bu.backbut2->w;
    SDL_BlitSurface(bu.backbut2,NULL,screen,&bu.backbutPos);
    SDL_Flip(screen);
    y=1;
    }else{
      played = 0;
    }
  }
}
  return y;
}
int menuPlayClicks(SDL_Event event, buttons bu, menuPlayGame mpg, control c, soundFX sfx){
  int y = 0;
  if(((event.button.x <= (mpg.computerPos.x + mpg.computer->w)) && (event.button.x >= mpg.computerPos.x)) && ((event.button.y >= mpg.computerPos.y) && (event.button.y <= (mpg.computerPos.y + mpg.computer->h)))) {
   if(c.soundMuted == 0){
  Mix_PlayChannel(-1, sfx.butClick, 0);
  }
  y=1;
  }else{
  if(((event.button.x <= (mpg.friendPos.x + mpg.friend->w)) && (event.button.x >= mpg.friendPos.x)) && ((event.button.y >= mpg.computerPos.y) && (event.button.y <= (mpg.friendPos.y + mpg.friend->h)))) {
   if(c.soundMuted == 0){
    Mix_PlayChannel(-1, sfx.butClick, 0);
  }
  y=2;
  }else{
  if(((event.button.x <= (bu.backbutPos.x + bu.backbut->w)) && (event.button.x >= bu.backbutPos.x)) && ((event.button.y >= bu.backbutPos.y) && (event.button.y <= (bu.backbutPos.y + bu.backbut->h)))) {
   if(c.soundMuted == 0){
   Mix_PlayChannel(-1, sfx.butClick, 0);
  }
  y = 0;
}else{
  y = -1;
}
  }
     }
  return y;
}
