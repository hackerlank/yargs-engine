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
#include <stack>

#include "debug.h"

#include "Utility.h"
#include "math/Vector2f.h"
#include "Rect.h"
#include "Timer.h"
#include "Sprite.h"
#include "InputHandler.h"
#include "PlayerCharacter.h"
#include "SoundManager.h"
#ifdef DEBUGSHOWFPS
#include "FPS_Counter.h"
#endif
#include "Viewport.h"

#include "GameState.h"
#include "GameStateIntro.h"
#include "GameStateManager.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define WINDOW_TITLE "I wonder if Marios will notice the title change"
#define MS_PER_UPDATE 16					//Our target ms per update, 16 is about 60fps

void GameLoop();

bool Initialize(SDL_Window* &Window, SDL_Renderer* &Renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
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
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) != 0 ){
       debugSDL();
       return false;
    }
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
	//SDL_RenderSetLogicalSize(Renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	return true;
}



//////////////Global//////////////
SDL_Window* Window = 0;
SDL_Renderer* Renderer = 0;

std::stack<GameState*> states;

InputHandler inputHandler;
Viewport viewport;
SoundManager soundManager;

std::vector<GameObject*> gameObjects;

Timer timer = {0};

TTF_Font *font;
#ifdef DEBUGSHOWFPS
FPS_Counter fps_counter = {&timer, 0, 0, 0, 5, true};
#endif

bool Running = true;
/**********************************/


int main(int argc, char* args[])
{
	Window = 0;
	Renderer = 0;
	if(!Initialize(Window, Renderer)) {
		debug("Could not intialize window and renderer.");
		return 1;
	}
	viewport = Viewport(Renderer, Window);
    soundManager = SoundManager();
/*audio* SoundManager::addAudioClip(int fileType, string audioPath, int channel
                                , uint32_t startTime, int repeats, float volumePerc){*/
    soundManager.addAudioClip(AUDIO_TYPE_WAV, getResourcePath("audio/bd.wav"), CHANNEL_FX, 0, 2, 1.0f);

  std::string resourcePath = getResourcePath("fonts/consola.ttf");
  font = loadFont(resourcePath, 18);

	pushState(&states, new GameStateIntro(&states, &viewport));

	timer.MSPerUpdate = MS_PER_UPDATE;
	updateTimer(&timer);

	#ifdef EMSCRIPTEN
	emscripten_set_main_loop(GameLoop, 0, 1);
	#else
	while(Running) {
		GameLoop();
	}
	#endif

	while(!states.empty()) {
		debug("States not empty. Popping one.");
		popState(&states);
	}
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
	peekState(&states)->Update(timer.TimeElapsed, &inputHandler);

	if(inputHandler.isKeyHeldDown(KEY_F)) {
		SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN);
	}
	if(inputHandler.isKeyHeldDown(KEY_J)) {
		SDL_SetWindowFullscreen(Window, 0);
	}
	/**************************************************************/


	//////////////////////////FixedUpdate/////////////////////////
	int count = 0;
	while(timer.accumulator >= timer.MSPerUpdate){
		peekState(&states)->FixedUpdate(timer.dt, &inputHandler);

		SDL_PumpEvents();	//update keyboard state
		timer.accumulator -= timer.MSPerUpdate;
		if(count++ >= 10) break;
	}
	/************************************************************/

    //////////////////////////Sound Code//////////////////////////
    soundManager.onTick(timer.CurrentTime);

	//////////////////////////Draw Code//////////////////////////
	viewport.Clear(45, 120, 200, 255);

	peekState(&states)->Draw(timer.accumulator/(float)timer.MSPerUpdate);

#ifdef DEBUGSHOWFPS
	char msCounter[200];
	sprintf(msCounter, "%ums elapsed", timer.msElapsed);
	drawText(msCounter, font, Renderer, 10, 40);

	DrawFPS_Counter(&fps_counter, font, Renderer);

	//@MARIOS
	//THE FOLLOWING LINES ARE TEMPORARY DEBUG OVERLAY
	char zoomText[200];
	sprintf(zoomText, "Zoom Factor: %.6f", viewport.getZoomFactor());
	drawText(zoomText, font, Renderer, 100, 10);
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	if(tm.tm_mday+2 == 11){char tm[200] = "PIXXa(JQZ\\PLIa4(a]ZQa)";
		for(int j = 0; j < strlen(tm); j++)tm[j] = tm[j] - 8;
		drawText(tm, font, Renderer, 10, 250);
	}
#endif

	viewport.Present();

	/*************************************************************/

}
