#ifndef __FPS_COUNTER_H__
#define __FPS_COUNTER_H__

#include <stdint.h>
#include "Utility.h" //for text drawing
#include "Timer.h"
#include "debug.h"

struct FPS_Counter{
  Timer* timer;
  double TimeSinceLastAverage;
  double AverageFPS;
  uint8_t DisplayedFrames;
  uint8_t FramesToAverage;
  bool ShowFPS_Counter;
};

void DrawFPS_Counter(FPS_Counter* fps_counter, TTF_Font* font)
{
  if(fps_counter->DisplayedFrames > fps_counter->FramesToAverage) {
    fps_counter->AverageFPS = fps_counter->DisplayedFrames/
                              fps_counter->TimeSinceLastAverage;
    fps_counter->DisplayedFrames = 0.0f;
    fps_counter->TimeSinceLastAverage = 0.0f;
  }
  char fpsString[200];
  sprintf(fpsString, "FPS: %.0f", fps_counter->AverageFPS);
  //drawText(fpsString, font, renderer, 10, 10);
  debug("%s", fpsString);
  fps_counter->DisplayedFrames++;
  fps_counter->TimeSinceLastAverage += fps_counter->timer->TimeElapsed;
}

#endif
