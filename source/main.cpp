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
														SDL_WINDOW_SHOWN);
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



	std::string fontResourcePath = getResourcePath("fonts/consola.ttf");
	TTF_Font *font = TTF_OpenFont(fontResourcePath.c_str(), 18);
	if(!font) {
		debugSDL();
	}

	std::string resourcePath;
	resourcePath = getResourcePath("grass.png");
	Sprite grass(Renderer, resourcePath);


	resourcePath = getResourcePath("alienYellow.png");
	Sprite PlayerYellowAlien = Sprite(Renderer, resourcePath);


	float xPos = 0;
	float yPos = 0;

	Timer timer = {0};
	timer.MSPerUpdate = MS_PER_UPDATE;
	updateTimer(&timer);
	bool Running = true;

	//TODO: Put this in some type of InputHandler
	const Uint8* keystate = SDL_GetKeyboardState(0);

	while(Running) {
		updateTimer(&timer);
//		debug("Main Loop");

		//Process Events//
		SDL_Event Event;
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
					debug("Event: SDL_KEYDOWN, xpos:%f ypos:%f", xPos, yPos);
				}break;

				case SDL_MOUSEBUTTONDOWN: {
					debug("Event: SDL_MOUSEBUTTONDOWN");
				}break;

				default: {
					//debug("Event: default");
				}break;
			}
		}

		SDL_RenderClear(Renderer);


		//FixedUpdate//
		while(timer.accumulator >= timer.MSPerUpdate){
//			debug("FixedUpdate()");
			float amount = 200.0f * timer.dt;

			if(keystate[SDL_SCANCODE_RIGHT]) {
				xPos += amount;
			}
			if(keystate[SDL_SCANCODE_LEFT]) {
				xPos -= amount;
			}
			if(keystate[SDL_SCANCODE_UP]) {
				yPos -= amount;
			}
			if(keystate[SDL_SCANCODE_DOWN]) {
				yPos += amount;
			}


			timer.accumulator -= MS_PER_UPDATE;
		}

		////////////



		//Draw Code//
		for(int i = 0; i < 10; i++) {
			for(int j = 0; j < 10; j++) {
				grass.draw(Renderer, i*(grass.getWidth()), j*grass.getHeight());
			}
		}
		PlayerYellowAlien.draw(Renderer, xPos, yPos);

		char msCounter[200];
		sprintf(msCounter, "%ums elapsed", timer.msElapsed);
		drawText(msCounter, font, Renderer, 10, 10);
		///////////

		SDL_RenderPresent(Renderer);


		//TODO: This is a bit sloppy but it prevents the cpu from spiking
		//			when the window is not in focused. Figure out why, this
		//			current code might cause me some other issues down the line.
		//			My guess is that vsync turns off when window not in focus.
		if((timer.OldTime + 17 - SDL_GetTicks()) < 1000) {
			SDL_Delay(timer.OldTime + 17 - SDL_GetTicks());
		}
	}


	return 0;
}
