#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>
#include <SDL2/SDL.h>

struct Timer {
  float TimeElapsed;      //since last frame (in seconds)
  uint32_t OldTime;
  uint32_t CurrentTime;
  uint32_t msElapsed;
  uint32_t accumulator;
  float dt;             //multiply times movement to get pixels per second
  uint8_t MSPerUpdate;  //TODO: decide on whether this can be changed live
};

void updateTimer(Timer* timer)
{
  timer->OldTime = timer->CurrentTime;
  timer->CurrentTime = SDL_GetTicks();
  timer->msElapsed = (timer->CurrentTime - timer->OldTime);
  timer->TimeElapsed = timer->msElapsed/1000.0f;
  timer->accumulator += timer->msElapsed;
  timer->dt = timer->MSPerUpdate / 1000.0f;
}



#endif
