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

  virtual void Draw(const float extrapolate) = 0;
  virtual void Update(const float dt, InputHandler* inputHandler) = 0;
  virtual void FixedUpdate(const float dt, InputHandler* inputHandler) = 0;
  virtual ~GameState() = 0;
};

#endif
