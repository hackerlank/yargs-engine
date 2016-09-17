#define GLEW_STATIC
#include <GL/glew.h>

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
#include "Timer.h"
#include "SpriteRenderer.h"
#include "InputHandler.h"
#include "PlayerCharacter.h"
#include "FPS_Counter.h"
#include "Viewport.h"

#include "GameState.h"
#include "GameStateIntro.h"
#include "GameStateManager.h"

#include "Shader.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define WINDOW_TITLE "Keep on chuggin'"
#define MS_PER_UPDATE 16					//Our target ms per update, 16 is about 60fps

void GameLoop();


//////////////Global//////////////
SDL_Window* Window = 0;
SDL_GLContext glContext;

std::stack<GameState*> states;

InputHandler inputHandler;

std::vector<GameObject*> gameObjects;

Timer timer = {0};

TTF_Font *font;
FPS_Counter fps_counter = {&timer, 0, 0, 0, 10, true};

bool Running = true;
/**********************************/

bool Initialize(SDL_Window* &Window)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0){
		debugSDL();
		return false;
	}
	Window = SDL_CreateWindow(WINDOW_TITLE,
														SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
														SCREEN_WIDTH, SCREEN_HEIGHT,
														SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );
	if(!Window){
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

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

	SDL_GLContext glContext = SDL_GL_CreateContext(Window);
  	if(!glContext) {
    	debugSDL();
    	return 1;
  	}

	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK) {
		printf("Could not intialize GLEW!\n");
		return -1;
	}

	SDL_GL_SetSwapInterval(1); //1 = vsync on, 0 = off

	return true;
}


int main(int argc, char* args[])
{
	Window = 0;
	if(!Initialize(Window)) {
		debug("Could not intialize window and renderer.");
		return 1;
	}

  	std::string resourcePath = getResourcePath("fonts/consola.ttf");
  	font = loadFont(resourcePath, 18);


	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(SCREEN_WIDTH),
					static_cast<GLfloat>(SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f);

//	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)SCREEN_WIDTH*2/(GLfloat)SCREEN_HEIGHT*2, 0.1f, 10000.0f);

	Shader simpleShader(getResourcePath("shaders/simple_shader.vs"),
						getResourcePath("shaders/simple_shader.fs"));

	pushState(&states, new GameStateIntro(&states, simpleShader));

	timer.MSPerUpdate = MS_PER_UPDATE;
	updateTimer(&timer);



  	simpleShader.setMat4("projection", projection);
  	simpleShader.setInt("image", 0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	#ifdef EMSCRIPTEN
	emscripten_set_main_loop(GameLoop, 0, 1);
	#else
	while(Running) {
		GameLoop();
	}
	#endif

	//Remove all states before exit
	while(!states.empty()) {
		popState(&states);
	}

	SDL_GL_DeleteContext(glContext);
	return 0;
}

void GameLoop()
{
	updateTimer(&timer);
	/////////////////////////Process Events/////////////////////////
	SDL_Event Event;
	//NOTE: SDL_PollEvent also calls SDL_PumpEvents which updates the 
	//      keyboard state that is used by inputHandler.
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


	//////////////////////////FixedUpdate/////////////////////////
	int count = 0;
	while(timer.accumulator >= timer.MSPerUpdate){
		peekState(&states)->FixedUpdate(timer.dt, &inputHandler);

		SDL_PumpEvents();	//update keyboard state
		timer.accumulator -= timer.MSPerUpdate;
		if(count++ >= 10) break;
	}
	/************************************************************/

	////////////////////////////Update/////////////////////////////
	peekState(&states)->Update(timer.TimeElapsed, &inputHandler);

	if(inputHandler.isKeyHeldDown(KEY_F)) {
		SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN);
	}
	if(inputHandler.isKeyHeldDown(KEY_J)) {
		SDL_SetWindowFullscreen(Window, 0);
	}
	/**************************************************************/

	//////////////////////////Draw Code//////////////////////////
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	peekState(&states)->Draw(timer.accumulator/timer.MSPerUpdate);

	char msCounter[200];
	sprintf(msCounter, "%ums elapsed", timer.msElapsed);
	//drawText(msCounter, font, Renderer, 10, 40);

	DrawFPS_Counter(&fps_counter, font);

	SDL_GL_SwapWindow(Window);
	/*************************************************************/

}
