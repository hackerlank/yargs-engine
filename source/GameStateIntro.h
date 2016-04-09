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

public:
  GameStateIntro(std::stack<GameState*> *states, Viewport* viewport)
                : GameState(viewport), background(viewport->getRenderer(), getResourcePath("background.png"))
  {
    this->states = states;
  }
  ~GameStateIntro()
  {

  }
  void Draw(const float extrapolate)
  {
    background.draw(viewport, 0, 0, 0);
  }
  void Update(const float dt, InputHandler* inputHandler)
  {
    if(inputHandler->isKeyHeldDown(KEY_SPACE)) {
      pushState(states, new GameStateMain(states, viewport));
    }
  }
  void FixedUpdate(const float dt, InputHandler* inputHandler)
  {

  }

  void onResume()
  {
    this->viewport->setZoomFactor(1.0f);
    this->viewport->setScreenCoords(0,0);
  }

  void onLeave()
  {
      //Nothing required for this
  }

};


#endif
