#ifndef __GAMESTATEMAIN_H__
#define __GAMESTATEMAIN_H__

#include <vector>
#include <stack>

#include "GameState.h"
#include "GameObject.h"
#include "PlayerCharacter.h"
#include "Sprite.h"

class GameStateMain : public GameState
{
private:
  std::vector<GameObject*> gameObjects;
  PlayerCharacter player1;
  PlayerCharacter player2;
  Sprite grass;

public:
  GameStateMain(std::stack<GameState*> *states, SDL_Renderer* Renderer);
  ~GameStateMain();
  virtual void Draw(Viewport* viewport, const float extrapolate);
  virtual void Update(const float dt, InputHandler* inputHandler, Viewport* viewport);
  virtual void FixedUpdate(const float dt, InputHandler* inputHandler);

};


#endif
