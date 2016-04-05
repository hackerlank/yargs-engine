#ifndef __GAMESTATEINTRO_H__
#define __GAMESTATEINTRO_H__

#include <stack>

#include "GameStateManager.h"
#include "GameStateMain.h"
#include "Sprite.h"

#include "Utility.h"
#include "Keys.h"

class GameStateIntro : public GameState
{
private:
  Sprite background;
  SDL_Renderer* renderer;

public:
  GameStateIntro(std::stack<GameState*> *states, SDL_Renderer* renderer)
                :background(renderer, getResourcePath("test.png"))
  {
    this->renderer = renderer;
    this->states = states;
  }
  ~GameStateIntro()
  {
    
  }
  virtual void Draw(Viewport* viewport, const float extrapolate)
  {
    background.draw(viewport, 0, 0, 0);
  }
  virtual void Update(const float dt, InputHandler* inputHandler, Viewport* viewport)
  {
    if(inputHandler->isKeyHeldDown(KEY_Y)) {
      pushState(states, new GameStateMain(states, renderer));
    }
  }
  virtual void FixedUpdate(const float dt, InputHandler* inputHandler)
  {

  }

};


#endif
