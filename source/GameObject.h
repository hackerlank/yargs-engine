#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <SDL2/SDL.h>
#include "InputHandler.h"

class GameObject
{
public:
  virtual void draw(SDL_Renderer* renderer, float interpolate) = 0;
  virtual void update(float dt, InputHandler* inputHandler) = 0;
};

#endif
