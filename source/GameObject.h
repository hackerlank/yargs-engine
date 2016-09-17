#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <SDL2/SDL.h>
#include "InputHandler.h"
#include "Viewport.h"

class GameObject
{
public:
  virtual void Draw(float interpolate){};
  virtual void FixedUpdate(const float dt, InputHandler* inputHandler){};
  virtual void Update(const float dt, InputHandler* inputHandler){};
};

#endif
