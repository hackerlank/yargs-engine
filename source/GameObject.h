#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <SDL2/SDL.h>
#include "InputHandler.h"
#include "Viewport.h"

class GameObject
{
public:
  virtual void Draw(Viewport* viewport, float interpolate) = 0;
  virtual void FixedUpdate(float dt, InputHandler* inputHandler) = 0;
  virtual void Update(float dt, InputHandler* inputHandler) = 0;
};

#endif
