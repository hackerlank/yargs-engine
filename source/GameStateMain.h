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
  int screenX, screenY;
  float zoomFactor;

public:
  GameStateMain(std::stack<GameState*> *states, Viewport* viewport);
  ~GameStateMain();
  void Draw(const float extrapolate);
  void Update(const float dt, InputHandler* inputHandler);
  void FixedUpdate(const float dt, InputHandler* inputHandler);
  void onResume();
  void onLeave();

};


#endif
