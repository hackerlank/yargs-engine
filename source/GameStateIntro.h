#ifndef __GAMESTATEINTRO_H__
#define __GAMESTATEINTRO_H__

#include <stack>

#include "GameStateManager.h"
#include "GameStateMain.h"
#include "SpriteRenderer.h"

#include "Utility.h"
#include "Keys.h"
#include "Shader.h"

class GameStateIntro : public GameState
{
private:
  Shader& shader;
  Texture2D background;
  Sprite backgroundSprite;
  Camera camera;
  SpriteRenderer renderer;

public:
  GameStateIntro(std::stack<GameState*> *states, Shader& shader)
                :shader(shader),
                background(getResourcePath("background.png")),
                backgroundSprite(background, 0, 0, background.width, background.height),
                camera(shader), 
                renderer(shader)
  {
    this->states = states;
  }
  ~GameStateIntro()
  {

  }
  void Draw(const float extrapolate)
  {
    renderer.draw(backgroundSprite, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f);
  }
  void Update(const float dt, InputHandler* inputHandler)
  {
    camera.Update(dt, inputHandler);
    if(inputHandler->isKeyHeldDown(KEY_SPACE)) {
      pushState(states, new GameStateMain(states, shader));
    }
  }
  void FixedUpdate(const float dt, InputHandler* inputHandler)
  {

  }

};


#endif
