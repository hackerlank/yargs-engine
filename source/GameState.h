#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

#include <stack>

#include "Viewport.h"
#include "InputHandler.h"
#include "PlayerCharacter.h"

class GameState
{
public:
  std::stack<GameState*> *states;

  virtual void Draw(Viewport* viewport, const float extrapolate) = 0;
  virtual void Update(const float dt, InputHandler* inputHandler, Viewport* viewport) = 0;
  virtual void FixedUpdate(const float dt, InputHandler* inputHandler) = 0;
  virtual PlayerCharacter *getTrackedPlayer(){ return NULL;} //Return NULL by default
  virtual ~GameState() = 0;
};

#endif
