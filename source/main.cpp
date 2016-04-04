#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

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
	return true;
}


int main(int argc, char* args[])
{
	SDL_Window* Window = 0;
	SDL_Renderer* Renderer = 0;
	if(!Initialize(Window, Renderer)) {
		debug("Could not intialize window and renderer.");
		return 1;
	}
	Viewport viewport = Viewport(Renderer, Window);

	std::string resourcePath;
	resourcePath = getResourcePath("fonts/consola.ttf");
	TTF_Font *font = loadFont(resourcePath, 18);

	resourcePath = getResourcePath("grass.png");
	Sprite grass(Renderer, resourcePath);

	resourcePath = getResourcePath("blackline.png");
	PlayerCharacter player1 = PlayerCharacter(Renderer, resourcePath);

	resourcePath = getResourcePath("alienGreen.png");
	PlayerCharacter player2 = PlayerCharacter(Renderer, resourcePath);
	player2.bindKeys(KEY_A, KEY_W, KEY_D, KEY_S, KEY_Q, KEY_E);

	std::vector<GameObject*> gameObjects;
	gameObjects.push_back(&player2);
	gameObjects.push_back(&player1);



	InputHandler inputHandler;

	Timer timer = {0};
	timer.MSPerUpdate = MS_PER_UPDATE;
	updateTimer(&timer);

	FPS_Counter fps_counter = {&timer, 0, 0, 0, 5, true};

	bool Running = true;

	while(Running) {
		updateTimer(&timer);
//		debug("Main Loop");

		//Process Events//
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

		//Update//
		if(inputHandler.isKeyHeldDown(KEY_LEFT)) {
			viewport.PanLeft(timer.TimeElapsed, 600.0f);
		}
		if(inputHandler.isKeyHeldDown(KEY_RIGHT)) {
			viewport.PanRight(timer.TimeElapsed, 600.0f);
		}
		if(inputHandler.isKeyHeldDown(KEY_UP)) {
			viewport.PanUp(timer.TimeElapsed, 600.0f);
		}
		if(inputHandler.isKeyHeldDown(KEY_DOWN)) {
			viewport.PanDown(timer.TimeElapsed, 600.0f);
		}

		for(int object = 0; object < gameObjects.size(); object++) {
			gameObjects[object]->Update(timer.TimeElapsed, &inputHandler);
		}
		/*********/


		//FixedUpdate//
		while(timer.accumulator >= timer.MSPerUpdate){
//			debug("FixedUpdate()");
			for(int object = 0; object < gameObjects.size(); object++) {
				gameObjects[object]->FixedUpdate(timer.dt, &inputHandler);
			}

			if(inputHandler.isKeyHeldDown(KEY_F)) {
				SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN);
			}
			if(inputHandler.isKeyHeldDown(KEY_J)) {
				SDL_SetWindowFullscreen(Window, 0);
			}

			SDL_PumpEvents();	//update keyboard state
			timer.accumulator -= timer.MSPerUpdate;
		}
		/************/


		//Draw Code//
		viewport.Clear(45, 120, 200, 255);

		for(int i = 0; i <= SCREEN_WIDTH/grass.getTextureWidth(); i++) {
			for(int j = 0; j <= SCREEN_HEIGHT/grass.getTextureHeight(); j++) {
				grass.draw(&viewport, i*(grass.getWidth()), j*grass.getHeight(), 0);
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
		/************/

	}//End Game Loop

	return 0;
}
