#ifndef __GAMESTATEMAIN_H__
#define __GAMESTATEMAIN_H__

#include <vector>
#include <stack>

#include "GameState.h"
#include "GameObject.h"
#include "PlayerCharacter.h"
#include "SpriteRenderer.h"
#include "Shader.h"
#include "Camera.h"

class GameStateMain : public GameState
{
private:
  std::vector<GameObject*> gameObjects;
  Texture2D grass;
  Sprite grassSprite;

  Texture2D playerTex;
  Sprite playerSprite;
  //PlayerCharacter player1;
  Camera camera;
  SpriteRenderer renderer;
  PlayerCharacter player2;

public:
  GameStateMain(std::stack<GameState*> *states, Shader& shader);
  ~GameStateMain();
  virtual void Draw(const float extrapolate);
  virtual void Update(const float dt, InputHandler* inputHandler);
  virtual void FixedUpdate(const float dt, InputHandler* inputHandler);

};


#endif
