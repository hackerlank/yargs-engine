#ifdef EMSCRIPTEN
#include <emscripten.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

#include "debug.h"

#include "Utility.h"
#include "math/Vector2f.h"
#include "Rect.h"
#include "Timer.h"
#include "Sprite.h"
#include "InputHandler.h"
#include "PlayerCharacter.h"
#include "FPS_Counter.h"
#include "Viewport.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define WINDOW_TITLE "Hello World"
#define MS_PER_UPDATE 16					//Our target ms per update, 16 is about 60fps
#define TRACKED_CHARACTER_PADDING 15

void GameLoop();

bool Initialize(SDL_Window* &Window, SDL_Renderer* &Renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		debugSDL();
		return false;
	}
	Window = SDL_CreateWindow(WINDOW_TITLE,
														SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
														SCREEN_WIDTH, SCREEN_HEIGHT,
														SDL_WINDOW_SHOWN );
	if(!Window){
		debugSDL();
		return false;
	}
	Renderer = SDL_CreateRenderer(Window, -1,
																SDL_RENDERER_ACCELERATED |
																SDL_RENDERER_PRESENTVSYNC);
	if(!Renderer){
		debugSDL();
		return false;
	}
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		debugSDL();
		return false;
	}
	if (TTF_Init() != 0){
		debugSDL();
		return false;
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
	SDL_RenderSetLogicalSize(Renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	return true;
}




SDL_Window* Window = 0;
SDL_Renderer* Renderer = 0;

InputHandler inputHandler;
Viewport viewport;

std::vector<GameObject*> gameObjects;
GameObject* trackedCharacter = NULL;

Timer timer = {0};

Sprite* grass;
TTF_Font *font;
FPS_Counter fps_counter = {&timer, 0, 0, 0, 5, true};

bool Running = true;

int main(int argc, char* args[])
{
	Window = 0;
	Renderer = 0;
	if(!Initialize(Window, Renderer)) {
		debug("Could not intialize window and renderer.");
		return 1;
	}
	viewport = Viewport(Renderer, Window);

	std::string resourcePath;
	resourcePath = getResourcePath("fonts/consola.ttf");
	font = loadFont(resourcePath, 18);

	resourcePath = getResourcePath("dirt.png");
	grass = new Sprite(Renderer, resourcePath);

	resourcePath = getResourcePath("blackline.png");
	PlayerCharacter player1 = PlayerCharacter(Renderer, resourcePath);
	player1.bindKeys(KEY_LEFT, KEY_UP, KEY_RIGHT, KEY_DOWN, KEY_Q, KEY_E);

	resourcePath = getResourcePath("alienGreen.png");
	PlayerCharacter player2 = PlayerCharacter(Renderer, resourcePath);
	player2.bindKeys(KEY_A, KEY_W, KEY_D, KEY_S, KEY_Q, KEY_E);

	trackedCharacter = &player2;

	gameObjects.push_back(&player2);
	gameObjects.push_back(&player1);

	timer.MSPerUpdate = MS_PER_UPDATE;
	updateTimer(&timer);

	#ifdef EMSCRIPTEN
	emscripten_set_main_loop(GameLoop, 0, 1);
	#else
	while(Running) {
		GameLoop();
	}
	#endif

	return 0;
}

void GameLoop()
{
	updateTimer(&timer);

	/////////////////////////Process Events/////////////////////////
	SDL_Event Event;
	//NOTE: SDL_PollEvent also calls SDL_PumpEvents which updates the keyboard
	//			state that is used by inputHandler.
	while(SDL_PollEvent(&Event)) {
		switch(Event.type) {
			case SDL_QUIT: {
				Running = false;
				debug("Event: SDL_QUIT");
			}break;
			case SDL_KEYDOWN: {
				if(Event.key.keysym.sym == SDLK_ESCAPE) {
					Running = false;
				}
			}break;
		}
	}
	/*************************************************************/


	////////////////////////////Update/////////////////////////////
	if(inputHandler.isKeyHeldDown(KEY_M)) {
		viewport.PanLeft(timer.TimeElapsed, 600.0f);
	}
	if(inputHandler.isKeyHeldDown(KEY_K)) {
		viewport.PanRight(timer.TimeElapsed, 600.0f);
	}
	if(inputHandler.isKeyHeldDown(KEY_J)) {
		viewport.PanUp(timer.TimeElapsed, 600.0f);
	}
	if(inputHandler.isKeyHeldDown(KEY_N)) {
		viewport.PanDown(timer.TimeElapsed, 600.0f);
	}

	if(inputHandler.isKeyHeldDown(KEY_I)) {
		viewport.ZoomIn(timer.TimeElapsed, .2f);
	}
	if(inputHandler.isKeyHeldDown(KEY_O)) {
		viewport.ZoomIn(timer.TimeElapsed, -.2f);
	}

	if(inputHandler.isKeyHeldDown(KEY_F)) {
		SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN);
	}
	if(inputHandler.isKeyHeldDown(KEY_J)) {
		SDL_SetWindowFullscreen(Window, 0);
	}

	for(int object = 0; object < gameObjects.size(); object++) {
		gameObjects[object]->Update(timer.TimeElapsed, &inputHandler);
	}
	/**************************************************************/


	//////////////////////////FixedUpdate/////////////////////////
	int count = 0;
	while(timer.accumulator >= timer.MSPerUpdate){

		for(int object = 0; object < gameObjects.size(); object++) {
			gameObjects[object]->FixedUpdate(timer.dt, &inputHandler);
		}

		SDL_PumpEvents();	//update keyboard state
		timer.accumulator -= timer.MSPerUpdate;
		if(count++ > 10) break;
	}
	/************************************************************/


	//////////////////////////Draw Code//////////////////////////
	viewport.Clear(45, 120, 200, 255);
	//Keep tracked object in viewport
	if(trackedCharacter != NULL){
		trackedCharacter->panToIncludeInViewport(&viewport, TRACKED_CHARACTER_PADDING, timer.accumulator/ (float) timer.MSPerUpdate);
	}

	for(int i = 0; i <= SCREEN_WIDTH/grass->getTextureWidth(); i++) {
		for(int j = 0; j <= SCREEN_HEIGHT/grass->getTextureHeight(); j++) {
			grass->draw(&viewport, i*(grass->getWidth()), j*grass->getHeight(), 0);
		}
	}

	for(int object = 0; object < gameObjects.size(); object++) {
		gameObjects[object]->Draw(&viewport,
															timer.accumulator/ (float) timer.MSPerUpdate);
	}

	char msCounter[200];
	sprintf(msCounter, "%ums elapsed", timer.msElapsed);
	drawText(msCounter, font, Renderer, 10, 40);

	DrawFPS_Counter(&fps_counter, font, Renderer);

	viewport.Present();
	/*************************************************************/

}
