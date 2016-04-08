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
                             Viewport *viewport)
                            : GameState(viewport), grass(viewport->getRenderer(), getResourcePath("dirt.png")),
                            player1(viewport->getRenderer(), getResourcePath("blackline.png")),
                            player2(viewport->getRenderer(), getResourcePath("alienGreen.png"))
{
  this->states = states;
  this->zoomFactor = 0.5f;
  this->screenX = 0;
  this->screenY = 0;
  std::string resourcePath;


  player2.bindKeys(KEY_A, KEY_W, KEY_D, KEY_S, KEY_Q, KEY_E);

  gameObjects.push_back(&player2);
  gameObjects.push_back(&player1);
}
GameStateMain::~GameStateMain()
{

}

void GameStateMain::Draw(const float extrapolate)
{

	for(int i = 0; i <= SCREEN_WIDTH/grass.getTextureWidth(); i++) {
		for(int j = 0; j <= SCREEN_HEIGHT/grass.getTextureHeight(); j++) {
			grass.draw(this->viewport, i*(grass.getWidth()), j*grass.getHeight(), 0);
		}
	}

  //TODO: This spot is temporary, need to move to Update()
  player2.panToIncludeInViewport(this->viewport, TRACKED_CHARACTER_PADDING, extrapolate);

  for(int object = 0; object < gameObjects.size(); object++) {
		gameObjects[object]->Draw(viewport, extrapolate);
    }

}

void GameStateMain::Update(const float dt, InputHandler* inputHandler)
{
  if(inputHandler->isKeyHeldDown(KEY_LEFT)) {
    viewport->PanLeft(dt, 600.0f);
  }
  if(inputHandler->isKeyHeldDown(KEY_RIGHT)) {
    viewport->PanRight(dt, 600.0f);
  }
  if(inputHandler->isKeyHeldDown(KEY_UP)) {
    viewport->PanUp(dt, 600.0f);
  }
  if(inputHandler->isKeyHeldDown(KEY_DOWN)) {
    viewport->PanDown(dt, 600.0f);
  }

  if(inputHandler->isKeyHeldDown(KEY_I)) {
    viewport->zoomBy(dt, .2f);
  }
  if(inputHandler->isKeyHeldDown(KEY_O)) {
    viewport->zoomBy(dt, -.2f);
  }

  if(inputHandler->isKeyHeldDown(KEY_Y)) {
    popState(states);
    return;
  }

  for(int object = 0; object < gameObjects.size(); object++) {
    gameObjects[object]->Update(dt, inputHandler);
  }
}

void GameStateMain::FixedUpdate(const float dt, InputHandler* inputHandler)
{
  for(int object = 0; object < gameObjects.size(); object++) {
    gameObjects[object]->FixedUpdate(dt, inputHandler);
  }
}

void GameStateMain::onResume(){
    this->viewport->setZoomFactor(this->zoomFactor);
    this->viewport->setScreenCoords(this->screenX,this->screenY);
}

void GameStateMain::onLeave(){
    //Keep track of our latest
    Vector2f sTL = viewport->getTopLeftCoords();
    this->screenX = sTL.x;
    this->screenY = sTL.y;
}
