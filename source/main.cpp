#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <stdlib.h>
#include <iostream>
#include <string>

#include "debug.h"

#include "Utility.h"
#include "math/Vector2f.h"
#include "Rect.h"
#include "Timer.h"
#include "Sprite.h"
#include "InputHandler.h"
#include "PlayerCharacter.h"
#include "FPS_Counter.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
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
	Initialize(Window, Renderer);

	std::string resourcePath;
	resourcePath = getResourcePath("fonts/consola.ttf");
	TTF_Font *font = loadFont(resourcePath, 18);

	resourcePath = getResourcePath("grass.png");
	Sprite grass(Renderer, resourcePath);

	resourcePath = getResourcePath("alienYellow.png");
	PlayerCharacter player1 = PlayerCharacter(Renderer, resourcePath);

	resourcePath = getResourcePath("alienGreen.png");
	PlayerCharacter player2 = PlayerCharacter(Renderer, resourcePath);
	player2.bindKeys(KEY_A, KEY_W, KEY_D, KEY_S);

	InputHandler inputHandler;
	Timer timer = {0};
	timer.MSPerUpdate = MS_PER_UPDATE;
	updateTimer(&timer);
	FPS_Counter fps_counter = {&timer, 0, 0, 0, 10, true};
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


		//FixedUpdate//
		while(timer.accumulator >= timer.MSPerUpdate){
//			debug("FixedUpdate()");
			player1.update(timer.dt, &inputHandler);
			player2.update(timer.dt, &inputHandler);

			if(inputHandler.isKeyPressed(KEY_F)) {
				SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN);
			}
			if(inputHandler.isKeyPressed(KEY_J)) {
				SDL_SetWindowFullscreen(Window, 0);
			}

			SDL_PumpEvents();	//update keyboard state
			timer.accumulator -= MS_PER_UPDATE;
		}
		////////////


		//Draw Code//
		SDL_RenderClear(Renderer);

		for(int i = 0; i <= SCREEN_WIDTH/grass.getWidth(); i++) {
			for(int j = 0; j <= SCREEN_HEIGHT/grass.getHeight(); j++) {
				grass.draw(Renderer, i*(grass.getWidth()), j*grass.getHeight());
			}
		}

		player1.draw(Renderer);
		player2.draw(Renderer);

		char msCounter[200];
		sprintf(msCounter, "%ums elapsed", timer.msElapsed);
		drawText(msCounter, font, Renderer, 10, 40);

		DrawFPS_Counter(&fps_counter, font, Renderer);
		SDL_RenderPresent(Renderer);
		///////////

		//TODO: This is a bit sloppy but it prevents the cpu from spiking
		//			when the window is not in focused. Figure out why, this
		//			current code might cause me some other issues down the line.
		//			My guess is that vsync turns off when window not in focus.
		if((timer.OldTime + 18 - SDL_GetTicks()) < 1000) {
			SDL_Delay(timer.OldTime + 18 - SDL_GetTicks());
		}
	}


	return 0;
}
