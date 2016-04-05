#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <SDL2/SDL.h>
#include "InputHandler.h"
#include "Viewport.h"

class GameObject
{
public:
  virtual void Draw(Viewport* viewport, float interpolate){};
  virtual void FixedUpdate(const float dt, InputHandler* inputHandler){};
  virtual void Update(const float dt, InputHandler* inputHandler){};

  virtual Vector2f getTopLeftCoords() = 0;
  virtual bool isInViewport(Viewport* viewport, int padding) = 0;
  virtual void panToIncludeInViewport(Viewport* viewport, int padding, float extrapolate) = 0;

};

#endif
