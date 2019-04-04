#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "graphics.h"
soundFX initSounds(){
  soundFX sfx;
  sfx.butHover = Mix_LoadWAV("Resources/hover.wav");
  sfx.butClick = Mix_LoadWAV("Resources/clicks.wav");
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
void showOffMenu(menu mc, SDL_Surface * screen){
  SDL_BlitSurface (mc.menuBack, NULL, screen, &mc.menuBackPos);
 SDL_BlitSurface (mc.playbut, NULL, screen, &mc.playbutPos);
 SDL_BlitSurface (mc.helpbut, NULL, screen, &mc.helpbutPos);
 SDL_BlitSurface (mc.aboutbut, NULL, screen, &mc.aboutbutPos);
 SDL_BlitSurface (mc.soundbut, NULL, screen, &mc.soundbutPos);
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
int menuClicks (menu mc, SDL_Surface * screen, SDL_Event event, control c, soundFX *sfx){
  int y = 0;
  if(((event.button.x <= (mc.playbutPos.x + mc.playbutPos.w)) && (event.button.x >= mc.playbutPos.x)) && ((event.button.y >= mc.playbutPos.y) && (event.button.y <= (mc.playbutPos.y + mc.playbutPos.h)))) {
  y=1;
}else{
  if(((event.button.x <= (mc.helpbutPos.x + mc.helpbutPos.w)) && (event.button.x >= mc.helpbutPos.x)) && ((event.button.y >= mc.helpbutPos.y) && (event.button.y <= (mc.helpbutPos.y + mc.helpbutPos.h)))) {
  y=2;
}else{
  if(((event.button.x <= (mc.aboutbutPos.x + mc.aboutbutPos.w)) && (event.button.x >= mc.aboutbutPos.x)) && ((event.button.y >= mc.aboutbutPos.y) && (event.button.y <= (mc.aboutbutPos.y + mc.aboutbutPos.h)))) {
 y=3;
}else{
  if(((event.button.x <= (mc.powerbutPos.x + mc.powerbutPos.w)) && (event.button.x >= mc.powerbutPos.x)) && ((event.button.y >= mc.powerbutPos.y) && (event.button.y <= (mc.powerbutPos.y + mc.powerbutPos.h)))) {
 y=4;
}else{
  if(((event.button.x <= (mc.soundbutPos.x + mc.soundbutPos.w)) && (event.button.x >= mc.soundbutPos.x)) && ((event.button.y >= mc.soundbutPos.y) && (event.button.y <= (mc.soundbutPos.y + mc.soundbutPos.h)))) {
   c.soundMuted = 1;
   mc.soundbutPos.h = mc.soundbut->h;
   mc.soundbutPos.w = mc.soundbut->w;
     SDL_BlitSurface(mc.soundbut2,NULL,screen,&mc.soundbutPos);
     SDL_Flip(screen);
     y = 5;
}
}
     }
   }
  }
return y;
}
