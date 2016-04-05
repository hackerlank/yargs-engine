#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <SDL2/SDL.h>
#include "InputHandler.h"
#include "Viewport.h"

class GameObject
{
public:
  virtual void Draw(Viewport* viewport, const float extrapolate)
  {
    //do nothing
  }
  virtual void FixedUpdate(const float dt, InputHandler* inputHandler)
  {
    //do nothing
  }
  virtual void Update(const float dt, InputHandler* inputHandler)
  {
    //do nothing
  }
};

#endif
