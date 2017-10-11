#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer
{
  public:
    void StartTimer();
    bool CheckTimer(int MilliSeconds);

  private:
    Uint32 StartTime;
    int elapsedTime;
};

#endif // TIMER_H
