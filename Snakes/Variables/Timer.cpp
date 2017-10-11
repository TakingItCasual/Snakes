#include "Timer.h"

void Timer::StartTimer(){
  StartTime = SDL_GetTicks();
}

bool Timer::CheckTimer(int MilliSeconds){
  elapsedTime = SDL_GetTicks()-StartTime;
  if(elapsedTime >= MilliSeconds){
    return true;
  }else{
    return false;
  }
}
