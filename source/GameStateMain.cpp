#ifdef EMSCRIPTEN
#include <SDL_ttf.h>
#else
#include <SDL2_ttf/SDL_ttf.h>
#endif

//Temporary defines
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TRACKED_CHARACTER_PADDING 15

#include "GameStateMain.h"

#include "GameStateManager.h"
#include "Utility.h"
#include <string>


GameStateMain::GameStateMain(std::stack<GameState*> *states,
                             Shader& shader)
                            :grass(getResourcePath("dirt.png")),
                            grassSprite(grass),
                            playerTex(getResourcePath("alienGreen.png")),
                            playerSprite(playerTex),
                            //player1("blackline.png", shader),
                            player2(playerSprite, renderer),
                            camera(shader),
                            renderer(shader)
{
  this->states = states;
  std::string resourcePath;


  player2.bindKeys(KEY_A, KEY_W, KEY_D, KEY_S, KEY_Q, KEY_E);

  gameObjects.push_back(&player2);
  //gameObjects.push_back(&player1);
}
GameStateMain::~GameStateMain()
{

}

void GameStateMain::Draw(const float extrapolate)
{

	for(int i = 0; i <= 10; i++) {
		for(int j = 0; j <= 10; j++) {
			renderer.draw(grassSprite, i*(grassSprite.getWidth()), j*(grassSprite.getHeight()), 0, 1.0, 1.0);
		}
	}

  //TODO: This spot is temporary, need to move to Update()
  //player2.panToIncludeInViewport(viewport, TRACKED_CHARACTER_PADDING, extrapolate);

  for(int object = 0; object < gameObjects.size(); object++) {
		gameObjects[object]->Draw(extrapolate);
	}

}

void GameStateMain::Update(const float dt, InputHandler* inputHandler)
{
  if(inputHandler->isKeyHeldDown(KEY_LEFT)) {
    //viewport->PanLeft(dt, 600.0f);
  }
  if(inputHandler->isKeyHeldDown(KEY_RIGHT)) {
    //viewport->PanRight(dt, 600.0f);
  }
  if(inputHandler->isKeyHeldDown(KEY_UP)) {
    //viewport->PanUp(dt, 600.0f);
  }
  if(inputHandler->isKeyHeldDown(KEY_DOWN)) {
    //viewport->PanDown(dt, 600.0f);
  }

  if(inputHandler->isKeyHeldDown(KEY_I)) {
    //viewport->ZoomIn(dt, .2f);
  }
  if(inputHandler->isKeyHeldDown(KEY_O)) {
    //viewport->ZoomIn(dt, -.2f);
  }

  if(inputHandler->isKeyHeldDown(KEY_Y)) {
    popState(states);
    return;
  }

  for(int object = 0; object < gameObjects.size(); object++) {
    gameObjects[object]->Update(dt, inputHandler);
  }

  camera.Update(dt, inputHandler);
  //viewport->followTarget(player2.getCenterPosition(), dt);
}

void GameStateMain::FixedUpdate(const float dt, InputHandler* inputHandler)
{
  for(int object = 0; object < gameObjects.size(); object++) {
    gameObjects[object]->FixedUpdate(dt, inputHandler);
  }
}
